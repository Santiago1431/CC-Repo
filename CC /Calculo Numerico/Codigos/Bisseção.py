import math


def bissecao(f, a, b, tol, max_iter):
    if f(a) * f(b) >= 0:
        print("O mC)todo da bisseC'C#o falhou (sinais iguais).")
        return None

    for _ in range(max_iter):
        p = (a + b) / 2  # Ponto mC)dio
        if abs(f(p)) < tol or (b - a) / 2 < tol:
            return p

        if f(a) * f(p) < 0:
            b = p
        else:
            a = p
    return p


print("-------------- Modo da bisseC'C#o -------------- \n")
print("by: Eurico Santiago\n \n ")

expressao = input("Digite a funC'C#o em termos de x (ex: x**4 - 8): ")
f = lambda x: eval(expressao)
tol = float(input("Digite a tolerC"ncia (ex: 1e-3): "))

print(f"f(x) = {expressao}")
print("insira os limites superiores e inferiores: \n")

a = float(input("limite inferior: "))
b = float(input("\nlimite superior: "))

k_formula = (math.log10(b - a) - math.log10(tol)) / math.log10(2)
k = math.ceil(k_formula)

print(f"Numero de interaC'C5es = {k}")
raiz = bissecao(f, a, b, tol, k)
print(f"\nRaiz aproximada: {raiz}")
