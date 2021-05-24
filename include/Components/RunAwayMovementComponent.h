#ifndef RUNAWAYMOVEMENTCOMPONENT_H
#define RUNAWAYMOVEMENTCOMPONENT_H

#include"Components/BaseEnemyMovementComponent.h"

class RunAwayMovementComponent : public BaseEnemyMovemementComponent
{
public:

	RunAwayMovementComponent() = default;

	virtual ~RunAwayMovementComponent() override = default;

	virtual void TickComponent(int64_t deltaTime = 0) override;

	
};

#endif
