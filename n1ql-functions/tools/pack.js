const fs = require('fs');
const path = require('path');

if (process.argv.length < 3) {
    console.error('Need at least 1 argument');
    return;
}

const filePath = process.argv[2];

fs.readFile(filePath, 'utf8', (error, data) => {
    if (error) {
        console.error(`Unable to read file ${process.argv[2]}, error : ${JSON.stringify(error)}`);
        return;
    }

    const parsedPath = path.parse(filePath);
    const fileName = parsedPath.name;
    const library = {
        'name': fileName,
        'code': data
    };

    const targetPath = `${parsedPath.dir}/${fileName}.json`;
    fs.writeFile(targetPath, JSON.stringify(library), error => {
        if (error) {
            console.error(`Unable to write to file ${targetPath}, error : ${JSON.stringify(error)}`);
        }
    });
});