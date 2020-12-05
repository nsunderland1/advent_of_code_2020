const fs = require('fs');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

lines
  .map(line => 
    parseInt(
      line.replace(/[BR]/g, "1").replace(/[FL]/g, "0")
    , 2))
  .sort()
  .forEach((val, i, arr) => {
    if (i > 0 && arr[i-1] === val-2) {
      console.log(val-1);
    }
  })

// const id = code => {
//   const v = code.slice(0, 7);
//   const h = code.slice(7, code.length);
//   return (
//       8 * v.split('').reduce((acc, chr) => chr === 'F' ? acc*2 : acc*2+1, 0)
//     + h.split('').reduce((acc, chr) => chr === 'L' ? acc*2 : acc*2+1, 0)
//   );
// }

// let prev;
// lines
//   .sort((a, b) => {
//     const [aV, bV] = [a, b].map(str => str.slice(0, 7));
//     const [aH, bH] = [a, b].map(str => str.slice(7, str.length));
//     if (a === b) {
//       return 0;
//     }
//     if (aV === bV) {
//       return aH < bH ? 1 : -1;
//     }
//     return aV < bV ? -1 : 1;
//   })
//   .map(id)
//   .forEach((seatid, i) => {
//     if (i !== 0 && seatid === prev-2) {
//       console.log(seatid+1);
//     }
//     prev = seatid;
//   })
