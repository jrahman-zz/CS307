module AsyncController
  # This is the rack endpoint that will be invoked asyncronously. It will be
  # wrapped in all the middleware that a normal Rails endpoint would have.
  class RackEndpoint
    attr_accessor :action

    def call(env)
      @action.call(env)
    end
  end

  @@endpoint = RackEndpoint.new

  def self.included(mod)
    # LocalCache isn't able to be instantiated twice, so it must be removed
    # from the new middleware stack.
    middlewares = Rails.application.middleware.middlewares.reject do |m|
      m.klass.name == "ActiveSupport::Cache::Strategy::LocalCache"
    end

    @@wrapped_endpoint = middlewares.reverse.inject(@@endpoint) do |a, e|
      e.build(a)
    end
  end

  # Called to finish an asynchronous request. Can be invoked with a block
  # or with the symbol of an action name.
  def finish_request(action_name=nil, &proc)
    async_callback = request.env.delete('async.callback')
    env = request.env.clone

    if !action_name
      env['async_controller.proc'] = proc
      action_name = :_async_action
    end

    @@endpoint.action = self.class.action(action_name)

    async_callback.call(@@wrapped_endpoint.call(env))
  end

  def _async_action
    instance_eval(&request.env['async_controller.proc'])
  end
end
