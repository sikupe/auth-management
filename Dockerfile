FROM alpine:latest AS build

RUN apk add --no-cache git gcc g++ cmake make

# Build and install OAT++
WORKDIR /deps

RUN git clone https://github.com/oatpp/oatpp.git
WORKDIR /deps/oatpp

RUN mkdir build && cd build && cmake .. && make install



# Build and install OAT++ Prostgresql
RUN apk add --no-cache postgresql-dev

WORKDIR /deps

RUN git clone https://github.com/oatpp/oatpp-postgresql.git
WORKDIR /deps/oatpp-postgresql

RUN mkdir build && cd build && cmake .. && make install

# Build Auth Management
# Copying src
WORKDIR /app
COPY . .

# Building
RUN mkdir build
RUN cd build && cmake .. && make

FROM alpine:latest AS prod
RUN apk add --no-cache libstdc++ libgcc postgresql-dev
RUN addgroup -S unpriviliged && adduser -S unpriviliged -G unpriviliged
USER unpriviliged

WORKDIR /app

COPY --from=build /app/build/main main
COPY sql sql

EXPOSE 8000

ENTRYPOINT ["./main"]
