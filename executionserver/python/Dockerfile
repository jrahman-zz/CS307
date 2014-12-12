FROM centos:latest
MAINTAINER Jason P. Rahman &lt;rahmanj@purdue.edu&gt;

RUN mkdir -p /srv/scripts
COPY run.sh /srv/scripts/
COPY codeexecutor.py /srv/scripts/
COPY __init__.py /srv/scripts/
COPY restserver.py /srv/scripts/

RUN mkdir -p /pip
COPY get-pip.py /pip/

RUN mkdir -p /wrapper
COPY wrapper /wrapper/

RUN mkdir -p /include
COPY include /include

WORKDIR /srv/scripts

# Install build tools
RUN yum -y install python-devel
RUN yum -y install binutils
RUN yum -y install make
RUN yum -y install gcc
RUN yum -y install gcc-c++

# Install needed modules
RUN python /pip/get-pip.py
RUN pip install flask

WORKDIR /wrapper

# Build module
RUN yum -y install boost-python-devel
RUN yum -y install boost-python
RUN python /wrapper/setup.py build
RUN python /wrapper/setup.py install

WORKDIR /srv/scripts
EXPOSE 5000
RUN chmod u+x run.sh

ENTRYPOINT ["/srv/scripts/run.sh"]
