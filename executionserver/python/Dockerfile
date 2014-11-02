FROM ubuntu
MAINTAINER Jason P. Rahman &lt;rahmanj@purdue.edu&gt;

RUN mkdir -p /srv/scripts
RUN mkdir -p /pip

COPY run.sh /srv/scripts/
COPY CodeExecutor.py /srv/scripts/
COPY __init__.py /srv/scripts/
COPY restserver.py /srv/scripts/
COPY get-pip.py /pip/

WORKDIR /srv/scripts

RUN apt-get update

RUN apt-get -y install software-properties-common

RUN add-apt-repository "deb http://archive.canonical.com/ubuntu $(lsb_release -sc) universe restricted multiverse"

RUN apt-get update
RUN dpkg -l | grep python
RUN apt-get -y install 'python-2.7'

RUN python3 /pip/get-pip.py
RUN pip install flask

RUN chmod u+x run.sh

ENTRYPOINT ["/srv/scripts/run.sh"]
