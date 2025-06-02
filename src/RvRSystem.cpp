
// Sistema de Guerra entre Reinos (RvR) - WYD

int ProcessSecTimer_DecideWinnerByMemberOnlineInRvR();
void ClearArea_RVR(int WinnerReino);
void DoTeleport_ReinoWins(int WinnerReino);
void Recompensa_ReinoWins(int WinnerReino);
void ProcessTimerWarReinoVsReino();
void ExamineWarReinoVsReino();

int ProcessSecTimer_DecideWinnerByMemberOnlineInRvR() {
    // Lógica de verificação de jogadores online e decisão de vitória

	int cTotalRed = 0, cTotalBlue = 0;

	cWinCont++;

	if (cWinCont < 30) //30 segundos
		return;

	cWinCont = 0;


	if (RVR[0].Started)
	{

		for (int i = 1; i < MAX_PLAYER; i++)
		{

			if (pUser(i)->Status != 22)
				continue;

			MOB& player = *(MOB*)GetMobFromIndex(i);


			if (GetPosX(i) >= 1053 && GetPosY(i) >= 1949 && GetPosX(i) <= 1247 && GetPosY(i) <= 2148)
			{
				// 7 = Blue
				// 8 = Red

				if (player.CapeInfo == 7)
					cTotalBlue++;

				if (player.CapeInfo == 8)
					cTotalRed++;
			}
		}
	}

	if (cTotalBlue)
		if (!cTotalRed)
			RVR[0].st_Points[BLUE].WarPoints = 3000;

	if (cTotalRed)
		if (!cTotalBlue)
			RVR[0].st_Points[RED].WarPoints = 3000;


    return 0; // Exemplo de retorno
}

void ClearArea_RVR(int WinnerReino) {
    // Lógica para limpar área do reino perdedor

	int CapeInfo;

	if (RVR[0].BlueWins)
		CapeInfo = 8;

	if (RVR[0].RedWins)
		CapeInfo = 7;

	//1053 1949 1247 2148 TODO mapa
	for (int i = 1; i < MAX_PLAYER; i++)
	{

		if (pUser(i)->Status != 22)
			continue;

		MOB& mob = *(MOB*)GetMobFromIndex(i);

		if (GetPosX(i) >= 1053 && GetPosY(i) >= 1949 && GetPosX(i) <= 1247 && GetPosY(i) <= 2148)
		{
			if (mob.CapeInfo == CapeInfo)
			{
				switch (mob.Info.CityID)
				{

				case 0:
					DoTeleport(i, ARMIA);
					break;

				case 1:
					DoTeleport(i, AZRAN);
					break;

				case 2:
					DoTeleport(i, ERION);
					break;
				}
			}
		}
	}
}

void DoTeleport_ReinoWins(int WinnerReino) {
    // Teleporte dos jogadores do reino vencedor

	int CapeInfo = 0;

	if (RVR[0].BlueWins)
		CapeInfo = 7;
	if (RVR[0].RedWins)
		CapeInfo = 8;

	//1053 1949 1247 2148 TODO mapa
	for (int i = 1; i < MAX_PLAYER; i++)
	{
		if (pUser(i)->Status != 22)
			continue;

		MOB& mob = *(MOB*)GetMobFromIndex(i);

		if (mob.CapeInfo != CapeInfo)
			continue;

		if (Player[i].RegiRVR)
		{
			switch (mob.CapeInfo)
			{

			case 7:
				DoTeleport(i, 1087, 2114);
				break;

			case 8:
				DoTeleport(i, 1217, 1982);
				break;
			}
		}
	}
}

void Recompensa_ReinoWins(int WinnerReino) {
    // Entrega de recompensas ao reino vencedor

	char szTMP[256];

	FILE* fs;

	int CapeInfo = 0;

	if (RVR[0].BlueWins)
		CapeInfo = 7;
	if (RVR[0].RedWins)
		CapeInfo = 8;

	//1053 1949 1247 2148 TODO mapa
	for (int i = 1; i < MAX_PLAYER; i++)
	{
		if (pUser(i)->Status != 22)
			continue;

		MOB& mob = *(MOB*)GetMobFromIndex(i);

		if (mob.CapeInfo != CapeInfo)
			continue;

		if (Player[i].RegiRVR)
		{
			if (mob.CapeInfo == CapeInfo)
			{
				st_Item Item;

				memset(&Item, 0, sizeof Item);

				Item.Index = 598;

				PutItem(i, &Item);

				//--------------------------------------------------------------

				memset(&Item, 0, sizeof Item);


				Item.Index = 3364;
				Item.EF1 = 61;
				Item.EFV1 = 20;

				PutItem(i, &Item);

				//--------------------------------------------------------------

				Player[i].Char[pUser(i)->CharPosition].Fame += 10;

				sprintf_s(szTMP, "Você recebeu FAME 10 Total [%d]", Player[i].Char[pUser(i)->CharPosition].Fame);
				SendClientMsg(i, szTMP);

				fopen_s(&fs, "ReinoWins.txt", "w");

				if (fs != NULL)
				{
					fprintf(fs, "%d", CapeInfo);
					fclose(fs);
				}

				ReadReinoWins();
			}
		}
	}
}

void ProcessTimerWarReinoVsReino() {
	// Lógica de ativação do evento baseado em horários


	int cDiaDaSem = PInt(0x00a5ea428);
	int cHor = PInt(0x00A5EA418);
	int cMin = PInt(0x00A5EA414);
	int cSeg = PInt(0x00A5EA410);

	//Segunda a Sexta
	if (cDiaDaSem > 0 && cDiaDaSem < 6)
	{
		if (!RVR[0].Happening && cHor == 21 || !RVR[0].Happening && RVR[0].EnableAdmin)
		{
			if (cMin >= 30 && cMin <= 35 || RVR[0].EnableAdmin)
			{
				if (cSeg >= 0 && cSeg <= 5 || RVR[0].EnableAdmin)
				{
					SendNotice("Guerra entre Reinos iniciará daqui 5 minutos !");
					RVR[0].Happening = true;
				}
			}
		}
	}
	else
	{
		//Sábado e Domingo
		if (cDiaDaSem == 0 || cDiaDaSem == 6)
		{
			if (!RVR[0].Happening && cHor == 22 || !RVR[0].Happening && RVR[0].EnableAdmin)
			{
				if (cMin >= 30 && cMin <= 35 || RVR[0].EnableAdmin)
				{
					if (cSeg >= 0 && cSeg <= 5 || RVR[0].EnableAdmin)
					{
						SendNotice("Guerra entre Reinos iniciará daqui 5 minutos !");
						RVR[0].Happening = true;
					}
				}
			}
		}
	}



	if (RVR[0].Happening)
		RVR[0].Time++;

	if (RVR[0].Time == 10)
		SendNotice("Para participar aguarde na cidade de Gelo !");

}

int currentTime;


void ExamineWarReinoVsReino() {
	// Execução contínua da guerra

	char szTMP[256];

	if (RVR[0].Happening)
	{
		if (RVR[0].Counter == 0)
		{
			if (RVR[0].Time == 5 * 60)
			{
				RVR[0].Counter = 1;

				for (int clientId = 1; clientId < MAX_PLAYER; clientId++)
				{
					if (pUser(clientId)->Status != 22)
						continue;

					MOB
						& indice = *(MOB*)GetMobFromIndex(clientId);


					if (indice.TargetX >= 3605 && indice.TargetY >= 3100 && indice.TargetX <= 3680 && indice.TargetY <= 3160)
					{
						if (!Player[clientId].CanWarRvR)
						{
							// 7 = Blue
							// 8 = Red
							int Reino = indice.CapeInfo & 0xFF;

							if (Reino == 7)
							{
								RemoveAffect(clientId, 24, 6);

								GetCurrentScore(clientId);
								SendScore(clientId);

								Player[clientId].RegiRVR = true;
								Player[clientId].AreaNoPVPCount = 0;
								Player[clientId].AttackPlayerCount = 0;
								Player[clientId].AttackMobCount = 0;
								DoTeleport(clientId, 1063, 2136);
							}

							if (Reino == 8)
							{
								RemoveAffect(clientId, 24, 6);

								GetCurrentScore(clientId);
								SendScore(clientId);

								Player[clientId].RegiRVR = true;
								Player[clientId].AreaNoPVPCount = 0;
								Player[clientId].AttackPlayerCount = 0;
								Player[clientId].AttackMobCount = 0;
								DoTeleport(clientId, 1237, 1960);
							}
						}
						else
						{
							SendClientMsg(clientId, "Você não pode participar !");
						}
					}
				}

				CreateMob("Contrato", 1062, 2130, "npc");
				CreateMob("Contrato", 1237, 1969, "npc");

				//Oracle_Layla

				CreateMob("Oracle_Layla", 1062 + Rand() % 5, 2130 + Rand() % 5, "npc");
				CreateMob("Oracle_Layla", 1237 + Rand() % 5, 1969 + Rand() % 5, "npc");
			}
		}

		// Cord menor: 1053 1949
		// Cord maior: 1247 2148

		else if (RVR[0].Counter == 1)
		{
			if (RVR[0].Time == 5 * 60 + 15)
			{
				SendNoticeArea(1250, 2151, 1056, 1952, "Aguarde no campo de batalha !");
			}

			if (RVR[0].Time == 5 * 60 + 20)
			{
				SendNoticeArea(1250, 2151, 1056, 1952, "2 minutos para iniciar a batalha !");
				RVR[0].Counter = 2;
			}
		}
		else if (RVR[0].Counter == 2)
		{
			if (RVR[0].Time == 5 * 60 + 30)
			{
				CreateMob("Torre'", 1075, 2126, "npc");
				CreateMob("Torre-", 1225, 1970, "npc");

				RVR[0].Counter = 3;
			}
		}

		else if (RVR[0].Counter == 3)
		{
			if (RVR[0].Time == 5 * 60 + 2 * 60)
			{
				RVR[0].Counter = 4;

				RVR[0].Started = true;

				SendNoticeArea(1250, 2151, 1056, 1952, "Guerra iniciada !!");

				CreateMob("Guard_RED", 1223, 1983, "npc");
				CreateMob("Guard_RED", 1213, 1979, "npc");
				CreateMob("Guard_RED", 1200, 1975, "npc");
				CreateMob("Guard_RED", 1191, 1971, "npc");

				CreateMob("Guard_RED", 1196, 1982, "npc");
				CreateMob("Guard_RED", 1206, 1988, "npc");
				CreateMob("Guard_RED", 1210, 1993, "npc");
				CreateMob("Guard_RED", 1239, 2012, "npc");

				CreateMob("Guard_RED", 1185, 1956, "npc");
				CreateMob("Guard_RED", 1222, 1974, "npc");

				CreateMob("Guard_RED", 1215, 2025, "npc");
				CreateMob("Guard_RED", 1202, 2012, "npc");
				CreateMob("Guard_RED", 1193, 2003, "npc");
				CreateMob("Guard_RED", 1185, 1994, "npc");
				CreateMob("Guard_RED", 1174, 1983, "npc");
				CreateMob("Guard_RED", 1153, 2002, "npc");

				for (int i = 0; i < 9; i++)
					CreateMob("Guard_RED", 1101, 1981, "npc");

				CreateMob("Guard_BLUE", 1070, 2104, "npc");
				CreateMob("Guard_BLUE", 1076, 2110, "npc");
				CreateMob("Guard_BLUE", 1083, 2117, "npc");
				CreateMob("Guard_BLUE", 1092, 2126, "npc");

				CreateMob("Guard_BLUE", 1079, 2121, "npc");

				CreateMob("Guard_BLUE", 1078, 2095, "npc");
				CreateMob("Guard_BLUE", 1087, 2104, "npc");
				CreateMob("Guard_BLUE", 1095, 2113, "npc");
				CreateMob("Guard_BLUE", 1110, 2125, "npc");

				CreateMob("Guard_BLUE", 1118, 2142, "npc");
				CreateMob("Guard_BLUE", 1060, 2085, "npc");

				CreateMob("Guard_BLUE", 1086, 2075, "npc");
				CreateMob("Guard_BLUE", 1096, 2084, "npc");
				CreateMob("Guard_BLUE", 1108, 2094, "npc");
				CreateMob("Guard_BLUE", 1122, 2108, "npc");
				CreateMob("Guard_BLUE", 1130, 2142, "npc");

				for (int i = 0; i < 9; i++)
					CreateMob("Guard_BLUE", 1196, 2101, "npc");
			}
		}

		else if (RVR[0].Counter == 4)
		{
			if (RVR[0].st_Points[BLUE].WarPoints >= 3000)
			{
				RVR[0].BlueWins = true;
				RVR[0].Started = false;

				sprintf_s(szTMP, "O Reino BLUE venceu Reino RED por [%d] a [%d] pontos !!", RVR[0].st_Points[BLUE].WarPoints, RVR[0].st_Points[RED].WarPoints);
				SendNotice(szTMP);

				RVR[0].Counter = 5;
			}

			if (RVR[0].st_Points[RED].WarPoints >= 3000)
			{
				RVR[0].RedWins = true;
				RVR[0].Started = false;

				sprintf_s(szTMP, "O Reino RED venceu Reino BLUE por [%d] a [%d] pontos !!", RVR[0].st_Points[RED].WarPoints, RVR[0].st_Points[BLUE].WarPoints);
				SendNotice(szTMP);

				RVR[0].Counter = 5;
			}

			if (RVR[0].Time >= 20 * 60)
			{
				if (RVR[0].st_Points[BLUE].WarPoints > RVR[0].st_Points[RED].WarPoints)
				{
					RVR[0].BlueWins = true;
					RVR[0].Started = false;

					sprintf_s(szTMP, "O Reino BLUE venceu Reino RED por [%d] a [%d] pontos !!", RVR[0].st_Points[BLUE].WarPoints, RVR[0].st_Points[RED].WarPoints);
					SendNotice(szTMP);

					RVR[0].Counter = 5;
				}

				else if (RVR[0].st_Points[RED].WarPoints > RVR[0].st_Points[BLUE].WarPoints)
				{
					RVR[0].RedWins = true;
					RVR[0].Started = false;

					sprintf_s(szTMP, "O Reino RED venceu Reino BLUE por [%d] a [%d] pontos !!", RVR[0].st_Points[RED].WarPoints, RVR[0].st_Points[BLUE].WarPoints);
					SendNotice(szTMP);

					RVR[0].Counter = 5;
				}

				else if (RVR[0].st_Points[RED].WarPoints == 0 && RVR[0].st_Points[BLUE].WarPoints == 0)
				{
					DeadMob(1053, 1949, 1247, 2148, 3);
					ClearArea(1247, 2148, 1053, 1949);

					memset(&RVR[0], 0, sizeof st_RVR);

					for (int i = 1; i < MAX_PLAYER; i++)
						Player[i].RegiRVR = false;
				}

				else if (RVR[0].st_Points[RED].WarPoints == RVR[0].st_Points[BLUE].WarPoints)
				{
					if (RVR[0].DeadTorre == 7)
					{
						RVR[0].BlueWins = true;
						RVR[0].Started = false;

						SendNotice("O Reino BLUE venceu Reino RED !");

						RVR[0].Counter = 5;

					}

					if (RVR[0].DeadTorre == 8)
					{

						RVR[0].RedWins = true;
						RVR[0].Started = false;

						SendNotice("O Reino RED venceu Reino BLUE !");

						RVR[0].Counter = 5;

					}
				}
			}
		}

		else if (RVR[0].Counter == 5)
		{
			ClearArea_RVR();

			currentTime = RVR[0].Time;

			RVR[0].Counter = 6;
		}

		else if (RVR[0].Counter == 6)
		{
			if (RVR[0].Time == currentTime + 30)
			{
				DeadMob(1053, 1949, 1247, 2148, 3);
				DoTeleport_ReinoWins();

			}

			if (RVR[0].Time == currentTime + 50)
			{

				if (RVR[0].BlueWins)
					CreateMob("Rei-Hekalotia", 1087, 2114, "npc");

				if (RVR[0].RedWins)
					CreateMob("Rei-Akelonia", 1217, 1982, "npc");
			}

			if (RVR[0].Time == currentTime + 60)
			{
				if (RVR[0].BlueWins)
					SendMessageNpc("Rei-Hekalotia", "Estou Honrado em ter vocês como meu exército");

				if (RVR[0].RedWins)
					SendMessageNpc("Rei-Akelonia", "Estou Honrado em ter vocês como meu exército");
			}

			if (RVR[0].Time == currentTime + 65)
			{
				if (RVR[0].BlueWins)
					SendMessageNpc("Rei-Hekalotia", "Como retribuição cada um recebera um item Caça Celestial");

				if (RVR[0].RedWins)
					SendMessageNpc("Rei-Akelonia", "Como retribuição cada um recebera um item Caça Celestial");
			}

			if (RVR[0].Time == currentTime + 70)
			{
				if (RVR[0].BlueWins)
					SendMessageNpc("Rei-Hekalotia", "Darei Fama a todos vocês");

				if (RVR[0].RedWins)
					SendMessageNpc("Rei-Akelonia", "Darei Fama a todos vocês");
			}

			if (RVR[0].Time == currentTime + 75)
			{
				if (RVR[0].BlueWins)
					SendMessageNpc("Rei-Hekalotia", "A experiência do reino Blue sera dobrada !");

				if (RVR[0].RedWins)
					SendMessageNpc("Rei-Akelonia", "A experiência do reino Red sera dobrada !");

			}

			if (RVR[0].Time == currentTime + 80)
			{
				if (RVR[0].BlueWins)
					SendMessageNpc("Rei-Hekalotia", "Parabéns a todos vocês Guerreiros !");

				if (RVR[0].RedWins)
					SendMessageNpc("Rei-Akelonia", "Parabéns a todos vocês Guerreiros !");
			}

			if (RVR[0].Time == currentTime + 85)
			{
				DeadMob(1053, 1949, 1247, 2148, 3);
			}

			if (RVR[0].Time == currentTime + 90)
			{
				if (RVR[0].BlueWins)
					CreateMob("Necromante", 1087, 2114, "CreateMob");

				if (RVR[0].RedWins)
					CreateMob("Necromante", 1217, 1982, "CreateMob");
			}


			if (RVR[0].Time == currentTime + 210)
			{
				Recompensa_ReinoWins();

				DeadMob(1053, 1949, 1247, 2148, 3);
				ClearArea(1247, 2148, 1053, 1949);
			}

			if (RVR[0].Time == currentTime + 250)
			{
				if (RVR[0].clientid > 0 && RVR[0].clientid < MAX_PLAYER)
				{
					if (pUser(RVR[0].clientid)->Status == 22)
					{
						Player[RVR[0].clientid].Char[pUser(RVR[0].clientid)->CharPosition].Fame += 15;

						sprintf_s(szTMP, "O jogador [%s] recebeu 15 pontos FAME por Derrubar a Torre", (char*)GetMobFromIndex(RVR[0].clientid));
						SendNotice(szTMP);

					}
				}


				memset(&RVR[0], 0, sizeof st_RVR);


				for (int i = 1; i < MAX_PLAYER; i++)
				{

					Player[i].RegiRVR = false;
					Player[i].AttackMobCount = 0;
					Player[i].AttackPlayerCount = 0;
				}

			}
		}
	}
}

