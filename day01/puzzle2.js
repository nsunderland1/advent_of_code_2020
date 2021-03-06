const fs = require('fs');

const data = fs.readFileSync('input', 'UTF-8');
const lines = data.split(/\r?\n/);

const nums = lines.map(line => parseInt(line, 10));
nums.forEach((numi, i) => {
  nums.forEach((numj, j) => {
    nums.forEach((numk, k) => {
      if (i !== j && j !== k && k !== i && numi + numj + numk === 2020) {
        console.log(numi * numj * numk);
      }
    });
  });
});
