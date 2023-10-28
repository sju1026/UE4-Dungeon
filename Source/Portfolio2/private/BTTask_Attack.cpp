// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MonsterAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "Monster.h"
#include "CombatInterface.h"


UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* const cont = owner_comp.GetAIOwner();
	AMonster* const npcBot = Cast<AMonster>(cont->GetPawn());
	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcBot))
	{
		if (montage_has_finished(npcBot)) {
			icombat->Execute_melee_attack(npcBot);
		}
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_Attack::montage_has_finished(AMonster* const npcBot)
{
	if (npcBot->MName == "Boss" && npcBot->health <= 100)
	{
		return npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->get_finalMontage());
	}
	return npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->get_montage());
}
