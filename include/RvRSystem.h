
// Header do Sistema RvR

int ProcessSecTimer_DecideWinnerByMemberOnlineInRvR();
void ClearArea_RVR(int WinnerReino);
void DoTeleport_ReinoWins(int WinnerReino);
void Recompensa_ReinoWins(int WinnerReino);
void ProcessTimerWarReinoVsReino();
void ExamineWarReinoVsReino();


typedef struct
{
	unsigned int Time;           // Tempo atual ou tempo restante da guerra
	char Counter;                // Contador genérico, talvez usado para tempo ou estado
	bool Happening;              // Indica se a guerra está ocorrendo no momento

	bool RedWins;                // Indica se a equipe vermelha venceu
	bool BlueWins;               // Indica se a equipe azul venceu

	bool Started;                // Indica se a guerra foi iniciada oficialmente

	int clientid;                // ID do cliente associado, possivelmente para mensagens ou logs

	bool EnableAdmin;            // Permite controle/administração manual da guerra

	BYTE DeadTorre;              // Quantidade de torres destruídas, ou status das torres

	struct
	{
		int WarPoints;          // Pontos acumulados pela equipe
	} st_Points[2];             // Array de pontos: 0 - Red, 1 - Blue

} st_RVR;


