# Simple Docker

Разработка и настройка докер-образа (на базе **nginx**) для собственного сервера на C и FastCgi, проверка безопасности и поиск уязвимостей образа при помощи **Dockle**, а также развёртывание проекта, состоящего сразу из нескольких докер-образов (через **Docker Compose**).

## Contents

1. [Ready-made docker](#part-1-ready-made-docker)
2. [Operations with container](#part-2-operations-with-container)
3. [Mini web server](#part-3-mini-web-server)
4. [Your own docker](#part-4-your-own-docker)
5. [Dockle](#part-5-dockle)
6. [Basic Docker Compose](#part-6-basic-docker-compose)

## Part 1. Ready-made docker
- Downloading the official docker image from nginx using `docker pull nginx` command.
	![part1-1](./misc/images/part1-1.png)
	
- Checking for the docker image with `docker images` command.
	![part1-2](./misc/images/part1-2.png)
	
- Running docker image with `docker run -d [image_id|repository]` and checking that the image is running with `docker ps` commands.
	![part1-3](./misc/images/part1-3.png)
	
- Viewing container information with `docker inspect [container_id|container_name]` command.
	![part1-4](./misc/images/part1-4.png)

- `docker inspect --size [container_id|container_name]` to define container size in bytes.
	![part1-5](./misc/images/part1-5.png)

- Container ip is **172.17.0.2** and port **80** is mapped.	![part1-6](./misc/images/part1-6.png)

- Stopping docker image with `docker stop [container_id|container_name]`and checking that the image has stopped with `docker ps` commands.
	![part1-7](./misc/images/part1-7.png)
	
- Running docker with ports **80** and **443** in container, mapped to the same ports on the local machine, with `docker run -d -p 80:80 -p 443:443 [image_id|repository]` command.
	![part1-8](./misc/images/part1-8.png)
	
- Checking that the nginx start page is available in the browser at *localhost:80*
	![part1-9](./misc/images/part1-9.png)
	
- Restarting docker container with `docker restart [container_id|container_name]`and checking the container is running with `docker ps` commands.
	![part1-10](./misc/images/part1-10.png)
	
## Part 2. Operations with container
- Reading the **nginx.conf** configuration file inside the docker container with `docker exec [container_id|container_name] cat /etc/nginx/nginx.conf` command.
	![part2-1](./misc/images/part2-1.png)

- *nginx.conf* file on a local machine configured to return the nginx server status page on the */status* path.
	![part2-2](./misc/images/part2-2.png)
	
- Copying locally created **nginx.conf** file inside the docker image using the `docker cp nginx.conf [container_id|container_name]:/etc/nginx/nginx.conf` command and reloading **nginx** configuration inside the docker image with `docker exec [container_id|container_name] nginx -s reload` command.
	![part2-3](./misc/images/part2-3.png)
	
- *localhost:80/status* returns the **nginx** server status page.
	![part2-4](./misc/images/part2-4.png)
	
- `docker export [container_id|container_name] > container.tar` and
`docker stop [container_id|container_name]` commands.
	![part2-5](./misc/images/part2-5.png)

- Deleting the image with `docker rmi -f [image_id|repository]` command without removing the container.
	![part2-6](./misc/images/part2-6.png)
	
- Deleting stopped container with `docker rm [container_id|container_name]` command.
	![part2-7](./misc/images/part2-7.png)
	
- Importing the container back using the `docker import container.tar [repository]`command.
	![part2-8](./misc/images/part2-8.png)
	
- Running the imported container with settings `docker run -i -t -d -p 80:80 -p 443:443 [image_id|repository] nginx -g "daemon off;"`
	![part2-9](./misc/images/part2-9.png)

- *Localhost:80/status* returns the **nginx** server status page.
	![part2-10](./misc/images/part2-10.png)
	
## Part 3. Mini web server
- Source code for mini server in C and FastCgi that will return a simple page saying `Hello World!`.
	![part3-1](./misc/images/part3-1.png)
	
- *nginx.conf* that will proxy all requests from port 81 to *127.0.0.1:8080*.
	![part3-2](./misc/images/part3-2.png)

- Using commands from [Part 1](#part-1-ready-made-docker) to download and run  docker with port **81** in container, mapped to the same port on the local machine.
	![part3-3](./misc/images/part3-3.png)

- Using commands from [Part 2](#part-2-operations-with-container) to copy locally created **nginx.conf** and source code for mini server files inside the docker image.
	![part3-4](./misc/images/part3-4.png)
	
- Executing a shell session inside a running Docker container with `docker exec -it [container_id|container_name] bash` command and installing packages required to compile and run mini server with `apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev` command.
	![part3-5](./misc/images/part3-5.png)
	
- Compiling source file for mini server into an executable, linking it with the **fcgi** library with `gcc -o [executable] [source_file.c] -lfcgi` command, running mini server via **spawn-fcgi** on port **8080** with `spawn-fcgi -p 8080 ./[executable]` command and reloading **nginx** configuration to proxy all requests from port **81** to **127.0.0.1:8080** with `nginx -s reload` command.
	![part3-6](./misc/images/part3-6.png)

- Checking that the inscription "Hello World!" is shown in the browser at the address *localhost:81*.
	<kbd>![part3-7](./misc/images/part3-7.png)
	
## Part 4. Your own docker
-  Writing the docker image for the created server using a ready-made image with **nginx** as base and script to compile and run server inside container.
	![part4-1](./misc/images/part4-1.png)
	![part4-2](./misc/images/part4-2.png)

- Building the written docker image with `docker build`, specifying the name and tag.
	![part4-3](./misc/images/part4-3.png)
	
- Checking with `docker images` that everything is built correctly.
	![part4-4](./misc/images/part4-4.png)

- Running the built docker image by mapping port **81** to **80** on the local machine and mapping the *./nginx* folder inside the container to the address where the **nginx** configuration files are located using `docker run -p 80:81 -v $(pwd)/server/nginx:/etc/nginx [repository:tag]` command.
	![part4-5](./misc/images/part4-5.png)

- Checking that the page of the written mini server is available on *localhost:80*.
	<kbd>![part4-6](./misc/images/part4-6.png)
	
- *nginx.conf* file on a local machine configured to return the nginx server status page on the */status* path.
	![part4-7](./misc/images/part4-7.png)

- Restarting docker image.
	![part4-8](./misc/images/part4-8.png)

- Validating proper mapping of the *./nginx* folder inside the container: after saving the file (on a local machine) and restarting the container, the configuration file inside the docker image updated itself without any extra steps (docker image rebuild is not required). Checking that *localhost:80/status* now returns a page with nginx status.
	![part4-9](./misc/images/part4-9.png)
	   
## Part 5. **Dockle**
- Using *.dockleignore* file in order to avoid errors or warnings when checking with dockle and using a ready-made image with **nginx** as base for the created server.
	![part5-1](./misc/images/part5-1.png)
- No errors or warnings when checking with with `dockle [image_id|repository]` command.
	![part5-2](./misc/images/part5-2.png)
	
## Part 6. Basic **Docker Compose**
- *docker-compose.yml* file.
	![part6-1](./misc/images/part6-1.png)

- *nginx.conf* file on a local machine for *docker-compose.yml* file to proxy all requests from port **8080** of the second container to port **81** of the first container.
	![part6-2](./misc/images/part6-2.png)

- No containers running.
	![part6-3](./misc/images/part6-3.png)

- Building and running the project with the `docker-compose build` and `docker-compose up` commands.
	![part6-4](./misc/images/part6-4.png)
	![part6-5](./misc/images/part6-5.png)

- Checking that the browser returns the page of the written mini server on *localhost:80* as before.	
	<kbd>![part6-6](./misc/images/part6-6.png)
	
	![finish](./misc/images/simple_docker.png)