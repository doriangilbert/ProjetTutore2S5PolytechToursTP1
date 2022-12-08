#include "paramcmdl.h"

char*ParamTypeChaine[] = {"entier", "reel", "chaine"};


/**
 * \fn char * ValeurParamToString(TParamDef * _tabParam, const int _index)
 * \brief fonction qui transforme la valeur d'un parametre en chaine de caractere
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _index indice du parametre a considerer dans le tableau
 * \return une nouvelle chaine (qu'il faudra libérer par la suite)
 */

char *ValeurParamToString(TParamDef *_tabParam, const int _index)
{
  if (_tabParam[_index].type == PTchaine)
  {
    char *buffer2 = malloc(sizeof(char *) * strlen(_tabParam[_index].valeur.chaine));
    strcpy(buffer2, _tabParam[_index].valeur.chaine);
    return buffer2;
  }
  else if (_tabParam[_index].type == PTentier)
  {
    char *buffer1 = malloc(sizeof(int));
    sprintf(buffer1, "%d", _tabParam[_index].valeur.entier);
    return buffer1;
  }
  else
  {
    char *buffer = malloc(sizeof(char *) * sizeof(float));
    sprintf(buffer, "%f", _tabParam[_index].valeur.reel);
    return buffer;
  }
}

/**
 * \fn PrintParam(TParamDef * _tabParam, const int _nbParam)
 * \brief fonction qui affiche a l'ecran les parametre, leur type et leur valeur
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \return neant
 */
void PrintParam(TParamDef *_tabParam, const int _nbParam)
{
  int i = 0;
  for (i = 0; i < _nbParam; i++)
  {
    printf("-%c %s ", _tabParam[i].lettre, _tabParam[i].nom);
    if (_tabParam[i].type == PTentier)
    {
      printf("(%s) ",ParamTypeChaine[2]);
    }
    else if (_tabParam[i].type == PTreel)
    {
      printf("(%s) ",ParamTypeChaine[1]);
    }
    else if (_tabParam[i].type == PTchaine)
    {
      printf("(%s) ",ParamTypeChaine[0]);
    }
    printf("[%s]",ValeurParamToString(_tabParam,i));
    printf("\n");
  }
}

/**
 * \fn int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[])
 * \brief fonction qui analyse la ligne de commande pour en extraire des valeurs pour les parametres
 *
 * \param[out] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \param[in] _argc nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv tableau qui contient les chaines de caracteres passees en arguments du programme
 * \return >=0 : nombre de parametres mis a jour, <0 : erreur
 */
int ReadParamFromCommandLine(TParamDef *_tabParam, const int _nbParam, const int _argc, const char *_argv[])
{
  int mj = 0;
  if (((_argc - 1) / 2) != _nbParam)
  {
    return -1;
  }
  int i = 1;
  for (i; i < (_argc - 1); i = i + 2)
  {
    int j = 0;
    for (j; j < _nbParam; j++)
    {
      char let = _argv[i][1];
      if (_tabParam[j].lettre == let)
      {
        if (_tabParam[j].type == PTchaine)
        {
          _tabParam[j].valeur.chaine = malloc(sizeof(char *) * strlen(_tabParam[j].valeur.chaine));
          strcpy((char *)_tabParam[j].valeur.chaine, _argv[i + 1]);
          mj++;
        }
        else if (_tabParam[j].type == PTentier)
        {
          _tabParam[j].valeur.entier = atoi(_argv[i + 1]);
          mj++;
        }
        else if (_tabParam[j].type == PTreel)
        {
          _tabParam[j].valeur.reel = atof(_argv[i + 1]);
          mj++;
        }
      }
    }
  }
  return mj;
}