FROM ubuntu:22.04
WORKDIR /app

# install app dependencies
RUN apt-get update && apt-get install -y build-essential
RUN apt-get install -y git
RUN apt-get install -y gfortran
# fpm
RUN apt-get install -y gcc

# install app
COPY cmd/run.sh /
RUN chmod +x /run.sh

# Settings
# create bashrc
RUN touch ~/.bashrc && chmod u+w ~/.bashrc
# customize bashrc
COPY cmd/prompt /
RUN sh -c 'cat /prompt >> ~/.bashrc'

# final configuration
ENV FLASK_APP=capp
EXPOSE 8000
CMD flask run --host 0.0.0.0 --port 8000