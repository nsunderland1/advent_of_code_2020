const fs = require('fs');
const { exit } = require('process');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

const rules = lines.map(line => {
  const words = line.split(' ');
  const colour = [words[0], words[1]].join(' ');
  const rhs = words.slice(4, words.length);
  if (rhs[0] === 'no') {
    return {colour, children: []};
  }
  const children = rhs.join(" ").split(", ");
  return {
    colour,
    children: children.map(child => {
      const pieces = child.split(" ");
      return {
        count: parseInt(pieces[0], 10),
        colour: [pieces[1], pieces[2]].join(" ")
      };
    })
  };
});

let colours = rules.reduce((acc, rule) => {
  return {
    [rule.colour]: {
      mark: "u",
      children: rule.children,
    },
    ...acc
  }
}, {});

const numbags = colour => colours[colour].children.reduce((sum, child) => child.count*(numbags(child.colour)+1) + sum, 0);
console.log(numbags('shiny gold'));

// let sortedcolours = [];
// const visit = clr => {
//   const colour = colours[clr];
//   if (colour.mark === "p") {
//     return;
//   }
//   if (colour.mark === "t") {
//     console.error("NOT A DAG");
//     exit(1);
//   }
//   colour.mark = "t";
//   colour.children.forEach(child => {
//     visit(child.colour);
//   });
//   colour.mark = "p";
//   sortedcolours.push(clr);
// }

// Object.keys(colours).forEach(colour => visit(colour));
// sortedcolours = sortedcolours.reverse();

// const containsSG = sortedcolours.slice(0, sortedcolours.indexOf("shiny gold")).reduceRight((acc, colour) =>
//   colours[colour].children.some(child => acc[child.colour] !== undefined) ? {[colour]: true, ...acc} : acc
// , {"shiny gold": true});

// console.log(Object.keys(containsSG).length - 1);


