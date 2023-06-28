#include "pa2m.h"
#include "src/hash.h"

#define VACIO 0

void prueba_creacion_destrucion()
{
	hash_t *hash_menor = hash_crear(1);
	hash_t *hash_mayor = hash_crear(4);
	pa2m_afirmar(hash_menor != NULL, "Hash con parametro menor al minimo.");
	pa2m_afirmar(hash_mayor != NULL, "Hash con parametro mayor al minimo.");
	pa2m_afirmar(hash_cantidad(hash_menor) == VACIO, "Hash menor vacio.");
	pa2m_afirmar(hash_cantidad(hash_mayor) == VACIO, "Hash mayor vacio.");
	pa2m_afirmar(hash_cantidad(NULL) == VACIO, "Hash nulo vacio.");
	hash_destruir(hash_menor);
	hash_destruir(hash_mayor);
}

void prueba_insercion_hash_con_algun_valor_NULL()
{
	hash_t *hash = hash_crear(3);
	void *anterior = NULL;
	char *clave = "clave";
	int valor = 10;
	pa2m_afirmar(hash_insertar(hash, NULL, &valor, &anterior) == NULL,
		     "Insertar clave NULL.");
	pa2m_afirmar(hash_insertar(NULL, clave, &valor, &anterior) == NULL,
		     "Insertar en un Hash NULL.");
	pa2m_afirmar(hash_insertar(hash, clave, &valor, &anterior) != NULL,
		     "Se inserta correctamente.");
	hash_destruir(hash);
}

void prueba_insertar_varios_elementos()
{
	hash_t *hash = hash_crear(8);
	void *anterior = NULL;
	char *clave_01 = "Argentina";
	int valor_01 = 3;
	char *clave_02 = "Jamaica";
	int valor_02 = 0;
	char *clave_03 = "Uruguay";
	int valor_03 = 2;
	hash_insertar(hash, clave_01, &valor_01, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 1, "Hash tiene un valor.");
	hash_insertar(hash, clave_02, &valor_02, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 2, "Hash tiene dos valores.");
	hash_insertar(hash, clave_03, &valor_03, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 3, "Hash tiene tres valores.");
	pa2m_afirmar(anterior == NULL, "Anterior nunca se modifico.");
	hash_destruir(hash);
}

void prueba_insertar_con_claves_repetidas()
{
	hash_t *hash = hash_crear(8);
	void *anterior = NULL;
	char *clave_01 = "Argentina";
	int valor_01 = 3;
	char *clave_02 = "Jamaica";
	int valor_02 = 0;
	char *clave_03 = "Uruguay";
	int valor_03 = 2;
	hash_insertar(hash, clave_01, &valor_01, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 1, "Hash tiene un valor.");
	hash_insertar(hash, clave_02, &valor_02, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 2, "Hash tiene dos valores.");
	hash_insertar(hash, clave_03, &valor_03, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 3, "Hash tiene tres valores.");
	hash_insertar(hash, clave_02, &valor_03, &anterior);
	pa2m_afirmar(anterior == &valor_02,
		     "Se almacena el valor reemplazado.");
	hash_insertar(hash, clave_02, &valor_02, &anterior);
	pa2m_afirmar(anterior == &valor_03,
		     "Se almacena el valor reemplazado.");
	hash_destruir(hash);
}

void pruebas_para_verificar_rehash()
{
	hash_t *hash = hash_crear(1);
	void *resultado = NULL;
	void *anterior = NULL;
	char clave[] = { 'a', 0 };
	char *valor_01 = "hola";
	char *valor_02 = "chau";

	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)
			hash_insertar(hash, clave, valor_01, NULL);
		else
			hash_insertar(hash, clave, valor_02, NULL);
		clave[0]++;
	}
	pa2m_afirmar(hash_cantidad(hash) == 10, "Se insertan 10 elementos.");
	resultado = hash_obtener(hash, "b");
	pa2m_afirmar(resultado == valor_02, "Valor insertado correctamente.");
	hash_insertar(hash, "a", valor_02, &anterior);
	pa2m_afirmar(anterior == valor_01,
		     "Se habia insertado correctamente el valor.");
	resultado = hash_obtener(hash, "a");
	pa2m_afirmar(resultado == valor_02,
		     "Se actualiza correctamente el valor en una clave.");
	hash_destruir(hash);
}

void pruebas_insercion()
{
	pa2m_nuevo_grupo("Insercion con algun valor NULL.");
	prueba_insercion_hash_con_algun_valor_NULL();
	pa2m_nuevo_grupo("Insertar varios elementos.");
	prueba_insertar_varios_elementos();
	pa2m_nuevo_grupo("Insertar con claves repetidas.");
	prueba_insertar_con_claves_repetidas();
	pa2m_nuevo_grupo("Verificar Rehash.");
	pruebas_para_verificar_rehash();
}

void pruebas_de_busqueda_obtener()
{
	hash_t *hash = hash_crear(3);
	void *anterior = NULL;
	char clave_01[] = { 'A', 'A', 'A', 0 };
	int valor_01 = 3;
	int valor_02 = 4;
	int valor_03 = 5;
	void *resultado = NULL;

	hash_insertar(hash, clave_01, &valor_01, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 1, "Hash tiene un valor.");

	clave_01[0]++;
	hash_insertar(hash, clave_01, &valor_02, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 2, "Hash tiene un valor.");

	resultado = hash_obtener(hash, "AAA");
	pa2m_afirmar((int *)resultado == &valor_01,
		     "Valor correcto encontrado.");

	resultado = hash_obtener(hash, "BAA");
	pa2m_afirmar((int *)resultado == &valor_02,
		     "Valor correcto encontrado.");

	clave_01[0]--;
	hash_insertar(hash, clave_01, &valor_03, &anterior);
	pa2m_afirmar(hash_cantidad(hash) == 2, "Hash con dos valores.");

	resultado = hash_obtener(hash, "AAA");
	pa2m_afirmar((int *)resultado == &valor_03, "Valor nuevo encontrado.");

	resultado = hash_obtener(hash, "Pepe");
	pa2m_afirmar(resultado == NULL, "Clave inexistente.");

	pa2m_afirmar(hash_obtener(NULL, "AAA") == NULL,
		     "No se puede obtener de un hash NULL.");

	pa2m_afirmar(hash_contiene(hash, "Pepe") == false,
		     "No contine clave inexistente.");
	pa2m_afirmar(hash_contiene(hash, "AAA") == true,
		     "Clave contenida en el hash.");

	pa2m_afirmar(hash_quitar(hash, "AAA") == &valor_03, "Valor eliminado.");
	pa2m_afirmar(hash_obtener(hash, "AAA") == NULL,
		     "No se encuentra el valor eliminado anteriormente.");

	hash_destruir(hash);
}

void pruebas_de_eliminar()
{
	hash_t *hash = hash_crear(1);
	char clave[] = { 'a', 0 };

	pa2m_afirmar(hash_quitar(NULL, clave) == NULL,
		     "Se prueba quitar de un hash nulo.");
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL,
		     "Se prueba quitar una clave nula.");
	pa2m_afirmar(hash_quitar(hash, clave) == NULL,
		     "Se prueba quitar de un hash vacio.");

	char *valores[8] = { "java", "c++", "python", "go",
			     ".net", "c",   "js",     "angular" };

	for (int i = 0; i < 8; i++) {
		hash_insertar(hash, clave, valores[i], NULL);
		clave[0]++;
	}

	pa2m_afirmar(hash_cantidad(hash) == 8, "Se insertan 8 elementos.");
	pa2m_afirmar(hash_quitar(hash, "z") == NULL,
		     "Se prueba quitar un elemento que no existia.");
	pa2m_afirmar(hash_quitar(hash, "b") == valores[1],
		     "Se prueba quitar un valor que si existia.");
	pa2m_afirmar(hash_quitar(hash, "b") == NULL,
		     "Se prueba quitar el elmento anteriormente quitado.");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS HASH ========================");
	pa2m_nuevo_grupo("Prueba creacion y destruccion.");
	prueba_creacion_destrucion();
	pa2m_nuevo_grupo("Pruebas de insercion.");
	pruebas_insercion();
	pa2m_nuevo_grupo("Pruebas de busqueda y obtener.");
	pruebas_de_busqueda_obtener();
	pa2m_nuevo_grupo("Pruebas de eliminar.");
	pruebas_de_eliminar();

	return pa2m_mostrar_reporte();
}
