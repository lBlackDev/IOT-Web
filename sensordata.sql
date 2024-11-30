CREATE DATABASE sensordata;
USE sensordata;

CREATE TABLE readings (
    id INT AUTO_INCREMENT PRIMARY KEY,
    humidity INT,
    temperature INT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
select * from readings;