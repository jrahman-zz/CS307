FROM ubuntu
MAINTAINER Jason P. Rahman &lt;rahmanj@purdue.edu&gt;

RUN mkdir -p /srv/scripts

COPY run.sh /srv/scripts/
COPY CodeExecutor.py /srv/scripts/
COPY __init__.py /srv/scripts/
COPY restserver.py /srv/scripts/
COPY response_templates /srv/scripts/

WORKDIR /srv/scripts

RUN chmod u+x run.sh

EXPOSE 8888

ENTRYPOINT ["/srv/scripts/run.sh"]
