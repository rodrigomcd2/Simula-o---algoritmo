# 💾 Simulador de Substituição de Páginas em C

Este projeto implementa uma simulação de algoritmos de substituição de páginas em sistemas operacionais, utilizando a linguagem C. A proposta é analisar o comportamento e o desempenho de três algoritmos clássicos: FIFO, LRU e CLOCK.

---

## 🎯 Objetivo

Este simulador foi desenvolvido como parte da disciplina **Arquitetura de Computadores** do curso de **Engenharia da Computação (UFMA)**, com o intuito de aplicar conceitos de gerenciamento de memória, paginação por demanda e análise de desempenho em algoritmos de substituição.

📎 [Link para o relatório do projeto](https://docs.google.com/document/d/1puS8HHpxpGD9D3cguG2hPKHlkDWglIymWVSXMM2spL8/edit?tab=t.0)

---

## ⚙️ Algoritmos implementados

- **FIFO (First-In First-Out)**  
  Remove a página mais antiga na memória.
- **LRU (Least Recently Used)**  
  Remove a página menos recentemente utilizada.
- **CLOCK**  
  Variante eficiente do LRU, utiliza um bit de referência para simular uso recente.

---

## 🧪 Parâmetros da simulação

- **Quantidade de quadros na memória física**: `3`
- **Quantidade de acessos simulados**: `12`
- **Sequência de acessos**:  
  `1, 2, 3, 2, 4, 1, 5, 2, 1, 2, 3, 4`

- **Custos por substituição simulados**:
  | Algoritmo | Tempo por substituição |
  |-----------|------------------------|
  | FIFO      | 8ms                   |
  | LRU       | 12ms                  |
  | CLOCK     | 10ms                  |

---

## 🖥️ Como compilar e executar

### Requisitos
- GCC instalado (recomendado via [MSYS2](https://www.msys2.org))
- VS Code (opcional)

### Passos:

```bash
# Compile
gcc simulador.c -o simulador

# Execute
./simulador

