/**
 * \file tp1_b.c
 * \brief 2ieme etape du TP IL
 * \author NM
 * \version 0.1
 * \date 17/11/2014
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

/**
 * \enum TParamType
 * \brief Constantes pour le type des parametres de la ligne de commande
 */
typedef enum
{
  PTentier, /**< un nombre entier */
  PTreel,   /**< un nombre reel */
  PTchaine  /**< une chaine de caracteres */
} TParamType;

/** constante chaine de caracteres pour l'affichage des types */
char *ParamTypeChaine[] = {"entier", "reel", "chaine"};

/**
 * \union TParamValue
 * \brief union permettant de  manipuler un entier/reel/chaine
 */
typedef union
{
  int entier;
  float reel;
  const char *chaine;
} TParamValue;

/**
 * \struct TParamDef
 * \brief represente un parametre de la ligne de commande (nom,type,valeur...)
 */
typedef struct
{
  char *nom;          /**< nom du parametre */
  TParamType type;    /**< type (entier,reel,chaine) */
  char lettre;        /**< lettre a utiliser sur la ligne de commande */
  TParamValue valeur; /**< valeur a affecter au parametre */
} TParamDef;

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
  if (_tabParam[_index].type = PTchaine)
  {
    char *buffer2 = malloc(sizeof(char *) * strlen(_tabParam[_index].valeur.chaine));
    strcpy(buffer2, _tabParam[_index].valeur.chaine);
    return buffer2;
  }
  else if (_tabParam[_index].type = PTentier)
  {
    int n = log10(_tabParam[_index].valeur.entier) + 1;
    char *buffer1 = malloc(sizeof(int) * n);
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
      printf("(entier) [%d]", _tabParam[i].valeur.entier);
    }
    else if (_tabParam[i].type == PTreel)
    {
      printf("(reel) [%f]", _tabParam[i].valeur.reel);
    }
    else if (_tabParam[i].type == PTchaine)
    {
      printf("(chaine) [%s]", _tabParam[i].valeur.chaine);
    }
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

/**
 * \fn int main (const int _argc, const char * _argv[])
 * \brief fonction principale
 *
 * \param[in] _argc : nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv : tableau qui contient les chaines de caracteres passes en arguments du programme
 * \return 0 si terminaison normale
 */
int main(const int _argc, const char *_argv[])
{
  /* declaration des paramtres avec leur type+valeurs par defaut */
  TParamDef tab_param[] = {
      {"serveur", PTchaine, 's', .valeur.chaine = "??"},
      {"appli", PTchaine, 'a', .valeur.chaine = ""},
      {"tours", PTentier, 't', .valeur.entier = 200}};
  int nb_param = 3;
  int result_arg;

  /* affichage des formats de parametre */
  printf("Valeurs par defaut :\n");
  PrintParam(tab_param, nb_param);
  /* analyse de la ligne de commande */
  result_arg = ReadParamFromCommandLine(tab_param, nb_param, _argc, _argv);
  /* affichage des nouveaux parametres */
  printf("Valeurs des parametres :\n");
  PrintParam(tab_param, nb_param);

  return 0;
}
