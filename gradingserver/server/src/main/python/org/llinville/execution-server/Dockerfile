FROM ubuntu
MAINTAINER Jason P. Rahman &lt;rahmanj@purdue.edu&gt;

RUN useradd -M executor

RUN mkdir -p /srv/scripts

ADD *.py /srv/scripts/

WORKDIR /srv

EXPOSE 8888

RUN chown -R executor /srv

ENV ENTRYPOINT restserver.py

CMD su executor && python /srv/scripts/${ENTRYPOINT}