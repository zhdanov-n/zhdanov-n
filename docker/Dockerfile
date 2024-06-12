FROM nginx:1.25.4

RUN apt-get update -o Acquire::http::No-Cache=True && \
    apt-get install -y gcc spawn-fcgi libfcgi-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY server/nginx/nginx.conf /etc/nginx/nginx.conf
COPY server/hello_world_fcgi.c /home
COPY server/start.sh /home/start.sh

WORKDIR /home

HEALTHCHECK --interval=5m --timeout=3s \
  CMD curl -f http://localhost:81/ || exit 1

ENTRYPOINT ["/bin/bash","/home/start.sh"]
