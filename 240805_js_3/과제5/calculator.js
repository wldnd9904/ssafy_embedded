class Calculator {
  #result = 0;

  add(num) {
    this.#result += num;
    return this;
  }

  multiply(num) {
    this.#result *= num;
    return this;
  }

  subtract(num) {
    this.#result -= num;
    return this;
  }

  divide(num) {
    if (num == 0) return this;
    this.#result /= num;
    return this;
  }

  getResult() {
    return this.#result;
  }
}

const calculator = new Calculator();

const result = calculator.add(5).multiply(2).subtract(3).divide(2).getResult();

console.log(result);
