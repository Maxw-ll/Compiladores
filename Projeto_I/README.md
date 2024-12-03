# Reconhecimento de Constantes Numéricas Reais com AFD

Este projeto implementa um **Autômato Finito Determinístico (AFD)** para reconhecer constantes numéricas reais conforme um padrão específico. O objetivo é identificar tokens numéricos válidos a partir de entradas fornecidas, seguindo as especificações descritas.

## Objetivo

Uma das classes de tokens presentes em linguagens de programação são as constantes numéricas reais. Este projeto visa implementar um AFD que reconheça tais constantes.

## Especificações

- O AFD deve **aceitar ou rejeitar** a entrada e, quando válido, **imprimir o lexema** correspondente.
- O AFD será implementado para aceitar apenas a **primeira cadeia de caracteres** que corresponder ao padrão definido.
- Caso nenhuma string case com o padrão, o sistema deve informar que **nenhum token foi reconhecido**.

## Exemplos de Funcionamento

- **Entrada:** `var := 3,14`  
  **Saída:** Aceito, token: `3,14`.

- **Entrada:** `var := 3.14`  
  **Saída:** Aceito, token: `3.14`.

- **Entrada:** `var := abc`  
  **Saída:** Nenhum token foi reconhecido.

