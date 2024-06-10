#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

typedef struct {
    int CRM;
    char nome[50];
    char especialidade[50];
} Medico;

typedef struct {
    int codigo;
    char nome[50];
    char dataNascimento[11]; 
    char sexo;
    char endereco[100];
    char telefone[15];
    char email[50];
} Paciente;

typedef struct {
    int codigo;
    char descricao[100];
} Procedimento;

typedef struct {
    int codigoMedico;
    int codigoPaciente;
    int codigoProcedimento;
    char data[50];
    char hora[10];
} RegistroProcedimentoPaciente;

typedef struct {
    int codigoPaciente;
    int codigoProcedimento;
    int codigoMedico;
    char data[50];
    char hora[10];
} ProcedimentoRealizado;

int validaNumero(char* str) {
    for (int i = 0; i < strlen(str); i++) 
	{
        if (!isdigit(str[i])) 
		{
            return 0;
        }
    }
    return 1;
}
int validaTexto(char* str) {
    for (int i = 0; i < strlen(str); i++) 
	{
        if (!isalpha(str[i])) 
		{
            return 0;
        }
    }
    return 1;
}

void excluiProcedimento() {
	fflush(stdin);
    FILE *arquivo;
    FILE *temp;
    Procedimento procedimento;
    int codigo;
    arquivo = fopen("procedimentos.bin", "rb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        temp = fopen("temp.bin", "wb");
        if (temp == NULL) {
            printf("Erro ao abrir o arquivo temporário.\n");
            fclose(arquivo);
        }
        else
        {
			printf("Informe o código do procedimento a ser excluído: ");
			fflush(stdin);
	        scanf("%d", &codigo);
	        while (fread(&procedimento, sizeof(Procedimento), 1, arquivo)) 
			{
	            if (procedimento.codigo != codigo) 
				{
	                fwrite(&procedimento, sizeof(Procedimento), 1, temp);
	            }
	        }
	        fclose(arquivo);
	        fclose(temp);
	        remove("procedimentos.bin");
	        rename("temp.bin", "procedimentos.bin");
	        printf("Procedimento excluído com sucesso!\n");
	        getch();
		}
    }
}
void excluiPaciente() {
    fflush(stdin);
    FILE *arquivo;
    FILE *temp;
    Paciente paciente;
    int codigo;
    arquivo = fopen("pacientes.bin", "rb");
    temp = fopen("temp.bin", "wb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        if (temp == NULL) 
		{
            printf("Erro ao abrir o arquivo temporário.\n");
            fclose(arquivo);
        } 
		else 
		{
            printf("Informe o código do paciente a ser excluído: ");
            fflush(stdin);
            scanf("%d", &codigo);
            int procedimentoAssociado = 0;
            RegistroProcedimentoPaciente registro;
            FILE *registroArquivo = fopen("regispacientes.bin", "rb");
            if (registroArquivo != NULL) 
			{
                while (fread(&registro, sizeof(RegistroProcedimentoPaciente), 1, registroArquivo)) 
				{
                    if (registro.codigoPaciente == codigo) 
					{
                        procedimentoAssociado = 1; 
                    }
                }
                fclose(registroArquivo);
            }
            if (procedimentoAssociado) 
			{
                printf("Não é possível excluir o paciente, pois há procedimentos associados a ele.\n");
                fclose(arquivo);
                fclose(temp);
                getch();
            } 
			else 
			{
                while (fread(&paciente, sizeof(Paciente), 1, arquivo)) 
				{
                    if (paciente.codigo != codigo) 
					{
                        fwrite(&paciente, sizeof(Paciente), 1, temp);
                    }
                }
                fclose(arquivo);
                fclose(temp);
                remove("pacientes.bin");
                rename("temp.bin", "pacientes.bin");
                printf("Paciente excluído com sucesso!\n");
                getch();
            }
        }
    }
}
void excluiMedico() {
	fflush(stdin);
    FILE *arquivo;
    FILE *temp;
    Medico medico;
    int CRM;
    arquivo = fopen("medicos.bin", "rb");
    temp = fopen("temp.bin", "wb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        if (temp == NULL) 
		{
            printf("Erro ao abrir o arquivo temporário.\n");
            fclose(arquivo);
            getch();
        } else {
            printf("Informe o CRM do médico a ser excluído: ");
            fflush(stdin);
            scanf("%d", &CRM);
            int procedimentoAssociado = 0;
            RegistroProcedimentoPaciente registro;
            FILE *registroArquivo = fopen("regispacientes.bin", "rb");
            if (registroArquivo != NULL) 
			{
                while (fread(&registro, sizeof(RegistroProcedimentoPaciente), 1, registroArquivo)) 
				{
                    if (registro.codigoMedico == CRM) 
					{
                        procedimentoAssociado = 1; 
                    }
                }
                fclose(registroArquivo);
            }

            if (procedimentoAssociado) 
			{
                printf("Não é possível excluir o médico, pois há procedimentos associados a ele.\n");
                fclose(arquivo);
                fclose(temp);
                getch();
            } else {
                while (fread(&medico, sizeof(Medico), 1, arquivo)) 
				{
                    if (medico.CRM != CRM) 
					{
                        fwrite(&medico, sizeof(Medico), 1, temp);
                    }
                }
                fclose(arquivo);
                fclose(temp);
                remove("medicos.bin");
                rename("temp.bin", "medicos.bin");
                printf("Médico excluído com sucesso!\n");
                getch();
            }
        }
    }
}
void relaProce() {
	fflush(stdin);
    FILE *arquivo;
    Procedimento procedimento;
    arquivo = fopen("procedimentos.bin", "rb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        printf("Relatório de Procedimentos:\n");
        printf("---------------------------------------------------\n");
        printf("| Código    | Descrição                           |\n");
        printf("---------------------------------------------------\n");
        while (fread(&procedimento, sizeof(Procedimento), 1, arquivo) == 1) {
            printf("| %d | %s |\n", procedimento.codigo, procedimento.descricao);
        }
        fclose(arquivo);
        printf("---------------------------------------------------\n");
        printf("Pressione qualquer tecla para retornar ao menu...");
        getch();
    }
}
void relaPaci() {
	fflush(stdin);
    FILE *arquivo;
    Paciente paciente;
    arquivo = fopen("pacientes.bin", "rb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        printf("Relatório de Pacientes:\n");
        printf("-------------------------------------------------------------\n");
        printf("| Código | Nome    | Data Nascimento | Sexo | Endereço             | Telefone       | Email            |\n");
        printf("-------------------------------------------------------------\n");
        while (fread(&paciente, sizeof(Paciente), 1, arquivo) == 1) 
		{
            printf("| %d | %s | %s | %c | %s | %s | %s |\n",paciente.codigo, paciente.nome, paciente.dataNascimento, paciente.sexo, paciente.endereco, paciente.telefone, paciente.email);
        }
        fclose(arquivo);
        printf("-------------------------------------------------------------\n");
        printf("Pressione qualquer tecla para retornar ao menu...");
        getch();
    }
}
void relaMedi() {
	fflush(stdin);
    FILE *arquivo;
    Medico medico;
    arquivo = fopen("medicos.bin", "rb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        printf("Relatório de Médicos:\n");
        printf("--------------------------------------------------\n");
        printf("| CRM       | Nome              | Especialidade    |\n");
        printf("--------------------------------------------------\n");
        while (fread(&medico, sizeof(Medico), 1, arquivo) == 1) 
		{
            printf("| %d | %s | %s |\n", medico.CRM, medico.nome, medico.especialidade);
        }
        fclose(arquivo);
        printf("--------------------------------------------------\n");
        printf("Pressione qualquer tecla para retornar ao menu...");
        getch();
    }
}
void relaLanca() {
    fflush(stdin);
    FILE *arquivo;
    ProcedimentoRealizado registro;
    arquivo = fopen("regispacientes.bin", "rb");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo de lançamentos.\n");
        getch();
    } 
	else 
	{
        printf("Relatório de Lançamentos:\n");
        printf("-------------------------------------------------------------\n");
        printf("| Código Paciente | Código Médico | Código Procedimento | Data | Hora | \n");
        printf("-------------------------------------------------------------\n");
        while (fread(&registro, sizeof(ProcedimentoRealizado), 1, arquivo) == 1) 
		{
            printf("| %d | %d | %d | %s | %s| \n", registro.codigoPaciente, registro.codigoMedico, registro.codigoProcedimento, registro.data, registro.hora);
        }
        fclose(arquivo);
        printf("-------------------------------------------------------------\n");
        printf("Pressione qualquer tecla para retornar ao menu...");
        getch();
    }
}
int medicoExiste(int CRM) {
	fflush(stdin);
    FILE *arquivo;
    Medico medico;
    arquivo = fopen("medicos.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de médicos.\n");
        getch();
    }
    else
    {
    	while (fread(&medico, sizeof(Medico), 1, arquivo) == 1) 
		{
	        if (medico.CRM == CRM) 
			{
	            fclose(arquivo);
	            return 1;
	        }
    	}

	}   
    fclose(arquivo);
    return 0;
}
int pacienteExiste(int codigo) {
	fflush(stdin);
    FILE *arquivo;
    Paciente paciente;
    arquivo = fopen("pacientes.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pacientes.\n");
        getch();
    }
	else
    {	
		while (fread(&paciente, sizeof(Paciente), 1, arquivo) == 1) 
		{
	        if (paciente.codigo == codigo) 
			{
	            fclose(arquivo);
	            return 1;
	        }
    	}
	}
    fclose(arquivo);
    return 0;
}
int procedimentoExiste(int codigo) {
	fflush(stdin);
    FILE *arquivo;
    Procedimento procedimento;
    arquivo = fopen("procedimentos.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de procedimentos.\n");
        getch();
    }
    else
    {	
		while (fread(&procedimento, sizeof(Procedimento), 1, arquivo) == 1) 
		{
	        if (procedimento.codigo == codigo) 
			{
	            fclose(arquivo);
	            return 1;
	        }
    	}
	}
    fclose(arquivo);
    return 0;
}
void regisproppaci() {
	fflush(stdin);
    FILE *arquivo;
    RegistroProcedimentoPaciente registro;
    arquivo = fopen("regispacientes.bin", "ab");
    system("cls");
    printf("=======FisioTec======\n");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo de registro de procedimentos e pacientes.\n");
        getch();
    } 
	else 
	{
        int CRM, codigoPaciente, codigoProcedimento;
        printf("Informe o código do médico: ");
        fflush(stdin);
        scanf("%d", &CRM);
        if (!medicoExiste(CRM)) 
		{
            printf("Médico com CRM %d não encontrado.\n", CRM);
            fclose(arquivo);
            getch();
        }
		else
		{
			printf("Informe o código do paciente: ");
	        scanf("%d", &codigoPaciente);
	        if (!pacienteExiste(codigoPaciente)) 
			{
	            printf("Paciente com código %d não encontrado.\n", codigoPaciente);
	            fclose(arquivo);
	            getch();
	        }
	        else
	        {
	        	printf("Informe o código do procedimento: ");
	        	fflush(stdin);
		        scanf("%d", &codigoProcedimento);
		        if (!procedimentoExiste(codigoProcedimento)) 
				{
		            printf("Procedimento com código %d não encontrado.\n", codigoProcedimento);
		            fclose(arquivo);
		            getch();
		        }
		        else
		        {
		        	printf("Informe a data do procedimento: ");
		        	fflush(stdin);
			        scanf("%s", registro.data);
			        printf("Informe a hora do procedimento (formato HH:MM): ");
                    fflush(stdin);
                    scanf("%s", registro.hora);
                    registro.codigoMedico = CRM;
			        registro.codigoMedico = CRM;
			        registro.codigoPaciente = codigoPaciente;
			        registro.codigoProcedimento = codigoProcedimento;
			        fwrite(&registro, sizeof(RegistroProcedimentoPaciente), 1, arquivo);
			        fclose(arquivo);
			        printf("Registro de procedimento associado a paciente e médico cadastrado com sucesso!\n");
			        getch();
				}     
			}       
		}  
    }
}
void cadProce() {
	fflush(stdin);
    Procedimento procedimento;
    FILE *arquivo;
    system("cls");
    printf("=======FisioTec======\n");
    arquivo = fopen("procedimentos.bin", "ab");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        char codigo[10];
        printf("Informe o código do procedimento: ");
        scanf("%s", codigo);
        while (!validaNumero(codigo)) 
		{
            printf("Código inválido. Informe novamente: ");
            scanf("%s", codigo);
        }
        while (procedimentoExiste(atoi(codigo))) 
		{
            printf("Já existe um procedimento com o código %s. Informe outro código: ", codigo);
            scanf("%s", codigo);
            while (!validaNumero(codigo)) 
			{
                printf("Código inválido. Informe novamente: ");
                scanf("%s", codigo);
            }
        }
        procedimento.codigo = atoi(codigo);
        printf("Informe a descrição do procedimento: ");
        scanf(" %s", procedimento.descricao);
        fwrite(&procedimento, sizeof(Procedimento), 1, arquivo);
        fclose(arquivo);
        printf("Procedimento cadastrado com sucesso!\n");
        getch();
    }
}
void cadPaci() {
	fflush(stdin);
    Paciente paciente;
    FILE *arquivo;
    system("cls");
    printf("=======FisioTec======\n");
    arquivo = fopen("pacientes.bin", "ab");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        char codigo[10];
        printf("Informe o código do paciente: ");
        scanf("%s", codigo);
        while (!validaNumero(codigo)) 
		{
            printf("Código inválido. Informe novamente: ");
            scanf("%s", codigo);
        }
        while (pacienteExiste(atoi(codigo))) 
		{
            printf("Já existe um paciente com o código %s. Informe outro código: ", codigo);
            scanf("%s", codigo);
            while (!validaNumero(codigo)) 
			{
                printf("Código inválido. Informe novamente: ");
                scanf("%s", codigo);
            }
        }
        paciente.codigo = atoi(codigo);
        printf("Informe o nome do paciente: ");
        scanf(" %s", paciente.nome);
        while (!validaTexto(paciente.nome)) 
		{
            printf("Nome inválido. Informe novamente: ");
            scanf(" %s", paciente.nome);
        }
        printf("Informe a data de nascimento (DD/MM/AAAA): ");
        scanf("%s", paciente.dataNascimento);
        printf("Informe o sexo (M/F): ");
        fflush(stdin);
        scanf("%c", &paciente.sexo);
        paciente.sexo = toupper(paciente.sexo); 
        while (paciente.sexo != 'M' && paciente.sexo != 'F') 
		{
            printf("Sexo inválido. Informe novamente (M/F): ");
            fflush(stdin);
            scanf("%c", &paciente.sexo);
            paciente.sexo = toupper(paciente.sexo); 
        }
        printf("Informe o endereço: ");
        scanf(" %s", paciente.endereco);
        printf("Informe o número de telefone (no formato (99) 99999-9999): ");
        scanf(" %s", paciente.telefone);
        printf("Informe o email: ");
        scanf(" %s", paciente.email);
        fwrite(&paciente, sizeof(Paciente), 1, arquivo);
        fclose(arquivo);
        printf("Paciente cadastrado com sucesso!\n");
        getch();
    }
}
void cadMedi() {
	fflush(stdin);
    Medico medico;
    FILE *arquivo;
    system("cls");
    printf("=======FisioTec======\n");
    arquivo = fopen("medicos.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        getch();
    } 
	else 
	{
        char CRM[10];
        printf("Informe o CRM do médico: ");
        scanf("%s", CRM);
        while (!validaNumero(CRM)) 
		{
            printf("CRM inválido. Informe novamente: ");
            scanf("%s", CRM);
        }
        while (medicoExiste(atoi(CRM))) 
		{
            printf("Já existe um médico com o CRM %s. Informe outro CRM: ", CRM);
            scanf("%s", CRM);
            while (!validaNumero(CRM)) 
			{
                printf("CRM inválido. Informe novamente: ");
                scanf("%s", CRM);
            }
        }       
        medico.CRM = atoi(CRM);
        printf("Informe o nome do médico: ");
        scanf("%s", medico.nome);
        while (!validaTexto(medico.nome)) 
		{
            printf("Nome inválido. Informe novamente: ");
            scanf("%s", medico.nome);
        }
        printf("Informe a especialidade do médico: ");
        scanf(" %s", medico.especialidade);
        fwrite(&medico, sizeof(Medico), 1, arquivo);
        fclose(arquivo);
        printf("Médico cadastrado com sucesso!\n");
        getch();
    }
}
void menu() {
    system("cls");
    printf("=======FisioTec======\n");
    printf("1-Cadastro\n");
    printf("2-Exclusao\n");
    printf("3-Lançamento\n");
    printf("4-relatorio\n");
    printf("5-Sair\n");
    printf("Opção: ");
}
void menuc() {
    system("cls");
    printf("=======FisioTec======\n");
    printf("=======CADASTRAR======\n");
    printf("1. Cadastrar Médico\n");
    printf("2. Cadastrar Paciente\n");
    printf("3. Cadastrar Procedimento\n");
    printf("4-Sair\n");
    printf("Opção: ");
}
void menul() {
    system("cls");
    printf("=======FisioTec======\n");
    printf("=======REGISTRAR======\n");
    printf("1. Registrar Procedimento\n");
    printf("2-Sair\n");
    printf("Opção: ");
}
void menur() {
    system("cls");
    printf("=======FisioTec======\n");
    printf("=======RELATORIO======\n");
    printf("1. Mostrar Relatório de Médicos\n");
    printf("2. Mostrar Relatório de Pacientes\n");
    printf("3. Mostrar Relatório de Procedimentos\n");
    printf("4. Mostrar Relatório de Lançamentos\n");
    printf("5-Sair\n");
    printf("Opção: ");
}
void menuE() {
    system("cls");
    printf("=======FisioTec======\n");
    printf("=======EXCLUSÃO======\n");
    printf("1. Excluir Médico\n");
    printf("2. Excluir Paciente\n");
    printf("3. Excluir Procedimento\n");
    printf("4. Voltar ao menu principal\n");
    printf("Opção: ");
}
void load()
{
printf("¦¦¦¦¦¦¦ ¦¦ ¦¦¦¦¦¦¦ ¦¦  ¦¦¦¦¦¦  ¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦  ¦¦¦¦¦¦ \n");
printf("¦¦      ¦¦ ¦¦      ¦¦ ¦¦    ¦¦    ¦¦    ¦¦      ¦¦      \n");
printf("¦¦¦¦¦   ¦¦ ¦¦¦¦¦¦¦ ¦¦ ¦¦    ¦¦    ¦¦    ¦¦¦¦¦   ¦¦      \n");
printf("¦¦      ¦¦      ¦¦ ¦¦ ¦¦    ¦¦    ¦¦    ¦¦      ¦¦      \n");
printf("¦¦      ¦¦ ¦¦¦¦¦¦¦ ¦¦  ¦¦¦¦¦¦     ¦¦    ¦¦¦¦¦¦¦  ¦¦¦¦¦¦\n");
Sleep(2500);
}
void executa() {
	fflush(stdin);
    int opcao;
    int op2;
    do {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                do {
                    menuc();
                    scanf("%d", &op2);
                    switch (op2) {
                        case 1:
                            cadMedi();
                            break;
                        case 2:
                            cadPaci();
                            break;
                        case 3:
                            cadProce();
                            break;
                    }
                } while (op2 != 4);
                break;
            case 2:
                do {
                    menuE();
                    scanf("%d", &op2);
                    switch (op2) {
                        case 1:
                            excluiMedico();
                            break;
                        case 2:
                            excluiPaciente();
                            break;
                        case 3:
                            excluiProcedimento();
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                    }
                } while (op2 != 4);
                break;
            case 3:
                do {
                    menul();
                    scanf("%d", &op2);
                    switch (op2) {
                        case 1:
                            regisproppaci();
                            break;
                    }
                } while (op2 != 2);
                break;
            case 4:
                do {
                    menur();
                    scanf("%d", &op2);
                    switch (op2) {
                        case 1:
                            relaMedi();
                            break;
                        case 2:
                            relaPaci();
                            break;
                        case 3:
                            relaProce();
                            break;
                        case 4:
                            relaLanca();
                            break;
                    }
                } while (op2 != 5);
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);
}
int main() {
    setlocale(LC_ALL, "Portuguese");
    load();   
    executa();
    return 0;
}
