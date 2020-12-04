const { getHashes } = require('crypto');
const fs = require('fs');

const IGNORE_EMPTY_LINES = false;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

let valid = 0;

const validators = [
  {
    key: "byr",
    func: val => {
      const byr = parseInt(val, 10);
      return 1920 <= byr && byr <= 2002;
    }
  },
  {
    key: "iyr",
    func: val => {
      const iyr = parseInt(val, 10);
      return 2010 <= iyr && iyr <= 2020;
    }
  },
  {
    key: "eyr",
    func: val => {
      const eyr = parseInt(val, 10);
      return 2020 <= eyr && eyr <= 2030;
    }
  },
  {
    key: "hgt",
    func: val => {
      const unit = val.substring(val.length-2, val.length);
      const size = parseInt(val.substring(0, val.length-2), 10);
      return (
           (unit === "cm" && 150 <= size && size <= 193)
        || (unit === "in" && 59 <= size && size <= 76)
      );
    }
  },
  {
    key: "hcl",
    func: RegExp.prototype.test.bind(/^#[a-f0-9]{6}$/)
  },
  {
    key: "ecl",
    func: RegExp.prototype.test.bind(/^((amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth))$/)
  },
  {
    key: "pid",
    func: RegExp.prototype.test.bind(/^[0-9]{9}$/)
  }
]

for (let i = 0; i < lines.length; i++) {
  let passport = {};
  while (lines[i] !== "") {
    const keyvals = lines[i].split(" ");
    passport = keyvals.reduce((acc, keyval) => {
      const [key, val] = keyval.split(":");
      return {[key]: val, ...acc};
    }, passport);
    i++;
  }
  valid += Number(validators.every(({key, func}) => {
    if (passport[key] == undefined) {
      return false;
    }
    return func(passport[key]);
  }));
}

console.log(valid);
