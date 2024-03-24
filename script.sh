#!/bin/bash

for i in $(seq 1 50); do
  # curl http://127.0.0.1:9999/  # replace with your actual URL
  curl -X POST -H "Content-Type: video/mp4" --data-binary "@./data/loc1/japan.mp4" http://127.0.0.1:8080/
  # curl -X GET -H "Content-Type: image/jpeg" http://127.0.0.1:9999/contact/output1706560967.jpeg --output image$i.jpeg
#   echo "Request $i sent"
done