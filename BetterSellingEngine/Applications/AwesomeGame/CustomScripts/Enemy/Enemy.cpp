#include "Enemy.h"
#include "../EnemyManager.h"
void Enemy::TakeDamage(int damage) {
	health -= damage;
	if (health <= 0) {
		EnemyManager::RemoveEnemy(gameObject);
	}
}