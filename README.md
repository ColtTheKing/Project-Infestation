# Project-Infestation
### Error Checking Syntax
```
if (object == nullptr)
{
  UE_LOG(LogInfestationError, Error, TEXT("%s: Object is NULL."), *this->GetFName().ToString());
  return;
}
```
[Unreal Logging Documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/logging-in-unreal-engine)

*NOTE: LogInfestationError and other Log categories can be found in the InfestationLogging header file.*
