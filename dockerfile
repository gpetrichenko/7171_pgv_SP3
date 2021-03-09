FROM ubuntu
COPY main_large.cpp .
RUN apt-get update && apt-get install gcc gcc-multilib g++ -y
RUN gcc -fno-pie -no-pie main_large.cpp -o lab3_large -g -lstdc++
CMD ./lab3_large
