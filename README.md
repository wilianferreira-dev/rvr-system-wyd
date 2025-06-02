# Sistema de Guerra entre Reinos (RvR) - WYD

Este projeto implementa um **Sistema de Guerra entre Reinos (RvR)** para o servidor privado do jogo WYD (With Your Destiny). O sistema foi desenvolvido por **Wilian Ferreira** e possui lógica completa de ativação de eventos, registro de jogadores, controle da batalha, determinação do reino vencedor, distribuição de recompensas e teleportes.

## 🎯 Funcionalidades

- **Ativação automática da Guerra** com base no dia e horário configurados.
- **Registro automático dos jogadores** na área de preparação.
- **Sistema de teleporte** para o campo de batalha conforme o reino.
- **Controle de status e pontos de guerra** para cada reino.
- **Decisão automática do vencedor** com base na presença dos jogadores.
- **Distribuição de recompensas** exclusivas para o reino vencedor.
- **Limpeza de área** após o fim da guerra.
- **Logs de vitória** e persistência dos resultados.

## 🛠️ Tecnologias

- Linguagem: **C++**
- Ambiente: **Servidor privado WYD**
- Manipulação de memória, status e efeitos em tempo real.
- Integração direta com o núcleo do servidor e sistemas de teleporte, inventário e mensagens.

## 📄 Estrutura do Sistema

### Funções principais:

- `ProcessSecTimer_DecideWinnerByMemberOnlineInRvR()`  
  Lógica de verificação de presença de jogadores e decisão automática do vencedor.

- `ClearArea_RVR(int WinnerReino)`  
  Limpeza e teleporte dos jogadores do reino perdedor.

- `DoTeleport_ReinoWins(int WinnerReino)`  
  Teleporte dos jogadores do reino vencedor para a área de premiação.

- `Recompensa_ReinoWins(int WinnerReino)`  
  Entrega de itens e fama aos jogadores do reino vencedor.

- `ProcessTimerWarReinoVsReino()`  
  Ativação automática da guerra baseado nos horários programados.

- `ExamineWarReinoVsReino()`  
  Lógica contínua da guerra, gerenciando registro, posicionamento, criação de NPCs e início da batalha.

## 🧩 Fluxo da Guerra

1. Sistema detecta dia e horário para iniciar a guerra.
2. Jogadores se registram automaticamente ao entrarem na área de preparação.
3. Após o tempo de espera, jogadores são teleportados para o campo de batalha.
4. Guerra é iniciada com criação de guardas e NPCs.
5. Sistema monitora pontos e jogadores presentes.
6. Determina o reino vencedor com base na presença online.
7. Teleporta jogadores, distribui recompensas e limpa a área.

## 🏆 Recompensas

- Item 598
- Item 3364 com efeito (EF1: 61, EFV1: 20)
- Fama: +10 pontos
- Notificação personalizada ao jogador.

## ⚠️ Notas importantes

- Este sistema é exclusivo para **servidores privados de WYD**.
- A lógica foi adaptada para o ambiente e as funções internas do servidor.
- Alguns métodos e variáveis são específicos da engine WYD, como `pUser()`, `GetMobFromIndex()`, `DoTeleport()`, `SendClientMsg()`.

## 🚀 Como usar

1. Integrar os arquivos fonte no núcleo do seu servidor WYD.
2. Configurar os horários e parâmetros conforme necessidade.
3. Compilar e iniciar o servidor.
4. Acompanhar logs e testes no ambiente de desenvolvimento.

## 📂 Arquivos

- `RvR.cpp` - Implementação principal do sistema de guerra.
- `RvR.h` - Cabeçalhos e definições (se aplicável).
- `README.md` - Documentação.

## 📃 Licença

**Uso pessoal e educacional**.  
Este sistema foi desenvolvido como contribuição à comunidade de desenvolvimento de servidores privados de WYD. Não é permitido o uso comercial sem autorização.

---

## ✉️ Contato

Desenvolvido por **Wilian Ferreira**  
Para dúvidas ou sugestões, entre em contato pelo GitHub ou e-mail.

