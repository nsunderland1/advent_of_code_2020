const fs = require('fs');

const IGNORE_EMPTY_LINES = true;

const dedup = array => array.filter(function (el, i, arr) {
	return arr.indexOf(el) === i;
});

const data = fs.readFileSync('input', 'UTF-8');
let groups = data.split("\n\n");
// let nums = groups.map(group => dedup(group.replace(/\n/g,"").split("").sort()).length);
let nums = groups.map(group => {
  const people = group.split("\n").filter(line => line !== "");
  const numpeople = people.length;
  return (
    people
      .join("")   // Get one string with all answers
      .split("")  // Get an array with all answers
      .sort()     // Arrange matching answers into groups
      .join("")   // Put them in a string
      .match(/([a-z])\1*/g) // Separate the groups from each other
      .filter(answer => answer.length === numpeople).length // Find the ones with the right size
  );
});
console.log(nums.reduce((acc, el) => acc + el));;