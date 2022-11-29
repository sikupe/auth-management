FROM alpine:latest AS build

RUN apk add --no-cache git gcc g++ cmake make

# Build and install OAT++
RUN git clone https://github.com/oatpp/oatpp.git
WORKDIR oatpp

RUN mkdir build && cd build && cmake .. && make install

# Build Auth Management
# Copying src
WORKDIR /app
COPY . .

# Building
RUN mkdir build
RUN cd build && cmake .. && make

FROM alpine:latest AS prod
RUN apk add --no-cache libstdc++ libgcc
RUN addgroup -S unpriviliged && adduser -S unpriviliged -G unpriviliged
USER unpriviliged

WORKDIR /app

COPY --from=build /app/build/main main

EXPOSE 8000

ENTRYPOINT ["./main"]
