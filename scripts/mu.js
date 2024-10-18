#!/usr/bin/env node

const fs = require("fs");
const mustache = require("mustache");

let template = "";

process.stdin.setEncoding("utf8");
process.stdin.on("data", function (chunk) {
  template += chunk;
});

process.stdin.on("end", function () {
  arr = template.split("razdeli");

  const output = mustache.render(arr[0], JSON.parse(arr[1]));

  process.stdout.write(output);
});

process.on("uncaughtException", (err) => {
  console.error(`Error: ${err.message}`);
  process.exit(1);
});
