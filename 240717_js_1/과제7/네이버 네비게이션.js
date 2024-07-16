const menu = document
  .querySelectorAll(".service_name")
  .values()
  .toArray()
  .map((node) => node.textContent);
console.log(menu);
