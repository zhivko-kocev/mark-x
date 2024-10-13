#!/usr/bin/env node

const fs = require('fs');
const mustache = require('mustache');

const jsonPath = process.argv[2];

function readJsonFile(path) {
    return JSON.parse(fs.readFileSync(path, 'utf8'));
}

let template = '';

process.stdin.setEncoding('utf8');
process.stdin.on('data', function(chunk) {
    template += chunk;
});

process.stdin.on('end', function() {

    const jsonData = readJsonFile(jsonPath);

    const output = mustache.render(template, jsonData);

    process.stdout.write(output);
});

process.on('uncaughtException', (err) => {
    console.error(`Error: ${err.message}`);
    process.exit(1);
});
