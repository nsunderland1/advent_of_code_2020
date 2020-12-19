const fs = require('fs');
const { exit } = require('process');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let [ruletext, texttext] = data.split(/\n\n/);
let rules = ruletext.split(/\r?\n/).map(rule => {
  const [numstr, rulestr] = rule.split(":").map(str => str.trim());
  const num = parseInt(numstr, 10);
  if (rulestr[0] === "\"") {
    return {
      num,
      typ: "char",
      char: rulestr[1]
    }
  } else {
    let pieces = rulestr.split("|").map(str => str.trim());
    let subrules = pieces.map(str => str.split(" ").map(str => parseInt(str, 10)));
    return {
      num,
      typ: "or",
      subrules
    }
  }
});

const rulemap = rules.reduce((acc, rule) => {
  let ruleobj = {};
  Object.keys(rule).forEach(el => { 
    if (el !== "num") {
      ruleobj[el] = rule[el];
    }
  });
  return {[rule.num]: ruleobj, ...acc};
}, {});

const dedup = arr => Array.from(new Set(arr));
// let sorted = [];
// const visit = rulenum => {
//   const rule = rulemap[rulenum];
//   if (rule.mark === "p") {
//     return;
//   }
//   if (rule.mark === "t") {
//     console.error("NOT A DAG");
//     exit(1);
//   }
//   rule.mark = "t";
//   const children = rule.typ === "char" ? [] : dedup(rule.subrules.flat());
//   children.forEach(child => {
//     visit(child);
//   });
//   rule.mark = "p";
//   sorted.push({num: rulenum, ...rule});
// }

// rules.forEach(rule => visit(rule.num));

// sorted.forEach(rule => {
//   if (rule.typ === "char") {
//     console.log("let rule"+rule.num+" = string \""+rule.char+"\" in");
//   } else {
//     const rhs = rule.subrules.map(subrule => "(list ["+subrule.map(num => "rule"+num).join(";")+"])").join("<|>");
//     console.log("let rule"+rule.num+" = ("+rhs+") >>| String.concat in");
//   }
// });
// const contains = (a, b) => {
//   if (a.typ === "char") {
//     return false;
//   }
//   return a.subrules.some(subrule => {
//     return subrule.some(rulenum => {
//       if (rulenum === b.num) {
//         return true;
//       }
//       return contains(rulemap[rulenum], b);
//     });
//   });
// }
// const comprules = (a, b) => {
//   if (a.typ === "char" && b.typ === "char") {
//     return 0;
//   }
//   if (a.typ === "char") {
//     return -1;
//   }
//   if (b.typ === "char") {
//     return 1;
//   }
//   if (contains(a, b)) {
//     return 1;
//   }
//   if (contains(b, a)) {
//     return -1;
//   }
//   return 0;
// };
// console.log(rules.sort(comprules));
let messages = texttext.split(/\n/);

const concat = (str, prefs, rule) => {
  return dedup(prefs.map(pref => {
    const strcut = str.slice(pref.length);
    return validprefixes(strcut, rule).map(suf => pref + suf);
  }).flat()); 
}
function validprefixes(str, rulenum) {
  const rule = rulemap[rulenum];
  if (rule.typ === "char") {
    if (str.length > 0 && str[0] === rule.char) {
      return [str[0]];
    } else {
      return [];
    }
  }
  let foo = dedup(rule.subrules.map(subrule => {
    return dedup(subrule.reduce((prefs, a) => concat(str, prefs, a), [""]));
  }).flat());
  return foo;
}

function isValid(str) {
  return validprefixes(str, 0).includes(str);
}

function isValidPart2(str) {
  let prefs = concat(str, concat(str, [""], 42), 42);
  for (let i = 2; ; i++) {
    let newprefs = prefs.slice();
    for (let j = 1; j < i; j++) {
      newprefs = concat(str, newprefs, 31);
      if (newprefs.includes(str)) {
        return true; 
      }
    }
    let updated = concat(str, prefs, 42);
    if (dedup(prefs.concat(...updated)).length === prefs.length) {
      return false;
    }
    prefs = updated;
  }
}

console.log(messages.filter(isValidPart2).length);
