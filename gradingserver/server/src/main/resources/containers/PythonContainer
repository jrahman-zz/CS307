FROM scratch
MAINTAINER Jason P. Rahman &lt;rahmanj@purdue.edu&gt;

RUN useradd -M executor

# TODO, need to add statements to include precompiled Python
# copy and the executor.py script
# Both will be mounted at /srv/

USER executor

WORKDIR /srv

EXPOSE 8888

RUN chown -R executor /srv && /srv/bin/python /srv/scripts/executor.py