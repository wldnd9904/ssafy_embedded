const first = () => {
  console.log("first:");
  for (let i = 1; i <= 10; i++) console.log(i);
};
const second = () => {
  console.log("second:");
  for (let i = 5; i >= -5; i--) console.log(i);
};
first();

second();
