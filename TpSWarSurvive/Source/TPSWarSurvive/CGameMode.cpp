#include "CGameMode.h"
#include "PlayerCharacter.h"

ACGameMode::ACGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}
