FROM ubuntu

RUN apt-get update && apt-get install -y build-essential curl unzip

CMD bash