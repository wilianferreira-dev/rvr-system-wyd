
# Sistema RvR – Guerra entre Reinos (WYD)

Este sistema foi desenvolvido para o jogo WYD, e simula eventos de Guerra entre Reinos, com as seguintes funcionalidades:

## Funcionalidades

- Registro automático dos jogadores por região.
- Teleporte de jogadores baseado em reino.
- Contagem de pontos de guerra.
- NPCs dinâmicos para defesa de base.
- Recompensas para o reino vencedor.
- Sistema de horários automáticos baseado no dia da semana.

## Estrutura

- `ProcessSecTimer_DecideWinnerByMemberOnlineInRvR`: Decide o vencedor com base nos jogadores online em campo.
- `ClearArea_RVR`: Remove jogadores do reino perdedor.
- `DoTeleport_ReinoWins`: Move os jogadores do reino vencedor.
- `Recompensa_ReinoWins`: Dá recompensas e fama ao reino vencedor.
- `ProcessTimerWarReinoVsReino`: Inicia a guerra baseado no horário/dia.
- `ExamineWarReinoVsReino`: Responsável pela execução da guerra em tempo real.

## Créditos

Desenvolvido por [Seu Nome ou Nickname]
