const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
// const {{modelName}}Router = require('./routes/{{modelName}}Routes');

const app = express();
const port = process.env.PORT || 3000;

// Middleware
app.use(cors());
app.use(express.json());

// Database connection
mongoose.connect('mongodb://localhost/{{modelName}}DB', {
    useNewUrlParser: true,
    useUnifiedTopology: true,
})
    .then(() => console.log('Connected to MongoDB'))
    .catch((err) => console.error('Could not connect to MongoDB', err));

// Routes
// app.use('/api/{{modelName}}s', {{modelName}}Router);

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send('Something broke!');
});

app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});

module.exports = app;