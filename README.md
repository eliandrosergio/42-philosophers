# Philosophers

Projeto *Philosophers* desenvolvido como parte do currículo da [Escola 42](https://www.42network.org/).

## Sobre o Projeto

O projeto *Philosophers* explora conceitos fundamentais de programação concorrente e paralela, utilizando threads e mutexes para simular o problema clássico dos Filósofos à Mesa de Jantar. 

O objetivo é implementar uma solução eficiente e conforme as regras, garantindo que os filósofos:
- Nunca acessem simultaneamente o mesmo garfo.
- Evitem deadlocks e race conditions.
- Respeitem as condições de término do programa.

## Atualizações na Versão 2.2

### Melhorias Implementadas
- **Conformidade com a Norminette**: O código foi ajustado para atender às exigências da norminette.
- **Otimizações em `routine` e `monitor`**: As funções desses arquivos foram revisadas e aprimoradas para maior eficiência e clareza.
- **Melhoria na Identificação dos Filósofos**: O ID dos filósofos agora é incrementado em +1 ao ser exibido no terminal, facilitando a leitura.

### Alterações no Comportamento
- Os filósofos continuam realizando suas ações (comer, pensar, etc.) mesmo após atingirem o número mínimo de refeições, a menos que:
  1. O programa termine.
  2. Um dos filósofos morra.
  3. Todos os filósofos tenham comido, pelo menos, o número mínimo de vezes.

## Como Compilar e Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu_usuario/philosophers.git
   cd philosophers
   make
   ./philo <número_de_filósofos> <tempo_para_morrer> <tempo_para_comer> <tempo_para_pensar> [número_de_vezes_para_comer]
