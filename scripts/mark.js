#!/usr/bin/env node

const inquirer = require("inquirer").default;
const fs = require("fs");
const path = require("path");

const askBasics = () => {
  const questions = [
    {
      name: "projectName",
      type: "input",
      message: "Enter the project name:",
    },
    {
      name: "projectType",
      type: "list",
      message: "Select project type:",
      choices: [
        { name: "Client Side Render", value: "csr" },
        { name: "Server Side Render", value: "ssr" },
      ],
    },
  ];

  return inquirer.prompt(questions);
};

const askFrontend = () => {
  const questions = [
    {
      name: "frontendType",
      type: "list",
      message: "Select a frontend type:",
      choices: [
        { name: "Vanilla", value: "vanilla" },
        { name: "React", value: "react" },
        { name: "Vue", value: "vue" },
        { name: "Preact", value: "preact" },
        { name: "Lit", value: "lit" },
        { name: "Svelte", value: "svelte" },
        { name: "Solid", value: "solid" },
        { name: "Qwik", value: "qwik" },
      ],
    },
  ];

  return inquirer.prompt(questions);
};

const askBackend = () => {
  const questions = [
    {
      name: "backendType",
      type: "list",
      message: "Select a backend type:",
      choices: [
        { name: "Spring", value: "spring" },
        { name: "Express", value: "express" },
        { name: ".NET", value: "dotnet" },
      ],
    },
  ];

  return inquirer.prompt(questions);
};

const askModel = () => {
  const questions = [
    {
      name: "addModels",
      type: "list",
      message:
        "Do you want to add models and generate endpoints to your project?",
      choices: [
        { name: "Yes", value: true },
        { name: "No", value: false },
      ],
    },
  ];
  return inquirer.prompt(questions);
};

const askModelDetails = async () => {
  const modelQuestions = [
    {
      name: "modelName",
      type: "input",
      message: "Enter model name:",
    },
    {
      name: "numberOfAttributes",
      type: "input",
      message: "How many attributes do you want to add?",
      validate: (input) => {
        const number = parseInt(input);
        return !isNaN(number) && number > 0
          ? true
          : "Please enter a valid number.";
      },
    },
  ];

  const answers = await inquirer.prompt(modelQuestions);
  const { numberOfAttributes } = answers;

  const attributes = [];

  for (let i = 0; i < numberOfAttributes; i++) {
    const attributeDetails = await inquirer.prompt([
      {
        name: "attributeName",
        type: "input",
        message: `Enter name for attribute ${i + 1}:`,
      },
      {
        name: "attributeType",
        type: "list",
        message: `Select type for attribute ${i + 1}:`,
        choices: [
          { name: "String", value: "string" },
          { name: "Integer", value: "int" },
          { name: "Boolean", value: "boolean" },
          { name: "Float", value: "float" },
          { name: "Double", value: "double" },
        ],
      },
    ]);

    attributes.push({
      name: attributeDetails.attributeName.toLowerCase(),
      Name:
        attributeDetails.attributeName.charAt(0).toUpperCase() +
        attributeDetails.attributeName.slice(1),
      type: attributeDetails.attributeType,
    });
  }

  const addMoreModelsQuestion = [
    {
      name: "addMoreModels",
      type: "list",
      message: "Do you want to add more models?",
      choices: [
        { name: "Yes", value: true },
        { name: "No", value: false },
      ],
    },
  ];

  const addMoreModelsAnswer = await inquirer.prompt(addMoreModelsQuestion);
  return {
    modelName: answers.modelName,
    attributes: attributes,
    addMoreModels: addMoreModelsAnswer.addMoreModels,
  };
};

const generateProjectJson = async () => {
  let basics = await askBasics();
  let frontend, backend, answers;
  if (basics.projectType === "csr") {
    frontend = await askFrontend();
  }
  backend = await askBackend();

  answers = await askModel();

  const models = [];

  if (answers.addModels) {
    let addMore = true;
    while (addMore) {
      const modelDetails = await askModelDetails();
      models.push({
        modelName: modelDetails.modelName.toLowerCase(),
        ModelName:
          modelDetails.modelName.charAt(0).toUpperCase() +
          modelDetails.modelName.slice(1),
        attributes: modelDetails.attributes,
      });

      addMore = modelDetails.addMoreModels;
    }
  }

  const projectJson = {
    projectName: basics.projectName,
    frontendType:
      typeof frontend !== "undefined" ? frontend.frontendType : "none",
    backendType:
      basics.projectType === "ssr"
        ? backend.backendType + "-ssr"
        : backend.backendType + "-csr",
    models: models,
  };

  return JSON.stringify(projectJson, null, 4); // Pretty-printing the JSON
};

const main = async () => {
  try {
    const data = await generateProjectJson();
    fs.writeFileSync("data.json", data);
  } catch (error) {
    console.error("An error occurred:", error);
    process.exit(1);
  }
};

main();
