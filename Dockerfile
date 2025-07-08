# Use an official C++ image
FROM gcc:latest

# Install OpenMP just in case
RUN apt-get update && apt-get install -y build-essential

# Create app directory
WORKDIR /app

# Copy your source code
COPY ./src ./src

# Set default build step
RUN g++ -o serial src/main_serial.cpp

# Set the default command
CMD ["./serial"]
