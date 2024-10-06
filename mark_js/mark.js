#!/usr/bin/env node

const inquirer = require("inquirer").default;
const { exec } = require("child_process");

const askQuestions = () => {
    const questions = [
        {
            name: "projectName",
            type: "input",
            message: "Enter the project name:"
        },
        {
            name: "backendType",
            type: "list",
            message: "Select a backend type:",
            choices: ["Spring Boot", "Express.js - (not implemented yet)", "Django  - (not implemented yet)"],
            default: "Spring Boot"
        },
        {
            name: "frontendType",
            type: "list",
            message: "Select a frontend type:",
            choices: ["react", "vue"],
            default: "react"
        },
        {
            name: "addModels",
            type: "confirm",
            message: "Do you want to add models and generate endpoints to your project?"
        }
    ];

    return inquirer.prompt(questions);
};

const askModelDetails = () => {
    return inquirer.prompt([
        {
            name: "modelName",
            type: "input",
            message: "Enter model name:"
        },
        {
            name: "attributes",
            type: "input",
            message: "Enter model attributes (comma separated, e.g., name:string, age:int):"
        },
        {
            name: "addMoreModels",
            type: "confirm",
            message: "Do you want to add more models?"
        }
    ]);
};

const generateProjectJson = async () => {
    const answers = await askQuestions();
    const models = [];

    if (answers["addModels"]) {
        let addMore = true;
        while (addMore) {
            const modelDetails = await askModelDetails();
            const modelAttributes = modelDetails.attributes.split(",").map(attr => {
                const [name, type] = attr.split(":");
                return { name: name.trim(), type: type.trim() };
            });

            models.push({
                modelName: modelDetails.modelName,
                attributes: modelAttributes
            });

            addMore = modelDetails["addMoreModels"];
        }
    }

    const projectJson = {
        projectName: answers.projectName,
        backendType: answers.backendType,
        frontendType: answers.frontendType,
        models: models
    };

    return JSON.stringify(projectJson);
};

// Wrap in an async function to use 'await'
const main = async () => {
    try {
        const data = await generateProjectJson();

        exec(`/usr/local/bin/mark-dir/mark_x '${data}'`, (error, stdout, stderr) => {
            if (error) {
                console.error(`Error executing mark: ${error}`);
                return;
            }

            console.log(`Output: ${stdout}`);
            console.log('Succesfully created the project!');
        });
    } catch (error) {
        console.error('An error occurred:', error);
    }
};

main(); // Call the main function
