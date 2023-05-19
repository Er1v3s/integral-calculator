function trapezoidalIntegration(a, b, n) {
  const h = (b - a) / n;
  let integralSum = 0;

  for (let i = 1; i < n; i++) {
    const x_i = a + i * h;
    const y_i = 2 * Math.cos(3 * x_i);
    integralSum += y_i;
  }
  const integral =
    (h / 2) * (2 * Math.cos(3 * a) + 2 * Math.cos(3 * b) + 2 * integralSum);
  return integral;
}

const a = 1;
const b = 3;
const n = 10;

const result = trapezoidalIntegration(a, b, n);
console.log("Przybliżona wartość całki: ", result);
