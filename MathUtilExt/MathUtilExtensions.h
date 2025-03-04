// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Misc/DefaultValueHelper.h"
#include "MathUtilExtensions.generated.h"


UCLASS()
class TOOLSCOLLECTION_API UMathUtilExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Add Rotator
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Rotator", meta = (CompactNodeTitle = "+", DisplayName = "Add (Rotator)"))
	static FRotator AddRotator(FRotator A, FRotator B)
	{
		FRotator Result;
		Result.Roll = (A.Roll + B.Roll);
		Result.Pitch = (A.Pitch + B.Pitch);
		Result.Yaw = (A.Yaw + B.Yaw);

		return Result;
	}
	// Subtract Rotator
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Rotator", meta = (CompactNodeTitle = "-", DisplayName = "Subtract (Rotator)"))
		static FRotator SubtractRotator(FRotator A, FRotator B)
	{
		FRotator Result;
		Result.Roll = (A.Roll - B.Roll);
		Result.Pitch = (A.Pitch - B.Pitch);
		Result.Yaw = (A.Yaw - B.Yaw);

		return Result;
	}
	// Divide Rotator
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Rotator", meta = (CompactNodeTitle = "/", DisplayName = "Divide (Rotator)", KeyWords = "/"))
	static FRotator DivideRotator(FRotator A, float B)
	{
		FRotator Result;
		Result.Roll = (A.Roll / B);
		Result.Pitch = (A.Pitch / B);
		Result.Yaw = (A.Yaw / B);

		return Result;
	}



	// Returns the absolute (negative) value of A
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (CompactNodeTitle = "-ABS", DisplayName = "Inverted Absolute (Float)"))
	static float InvertedAbsFloat(double A)
	{
		return (abs(A) * -1.0);
	}
	// Returns the absolute (negative) value of A
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (CompactNodeTitle = "-ABS", DisplayName = "Inverted Absolute (Integer)"))
		static int32 InvertedAbsInt(int32 A)
	{
		return (abs(A) * -1.0);
	}
	// Returns the absolute (negative) value of A
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (CompactNodeTitle = "-ABS", DisplayName = "Inverted Absolute (Integer64)"))
		static int64 InvertedAbsInt64(int64 A)
	{
		return (abs(A) * -1.0);
	}



	// Returns the signed 32-bit integer limit
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math", meta = (CompactNodeTitle = "32 LIMIT", DisplayName = "Integer Limit"))
	static void IntLimit(int32& Positive, int32& Negative)
	{
		Positive = 2147483647;
		Negative = -2147483647;
	}
	// Returns the signed 64-bit integer limit
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math", meta = (CompactNodeTitle = "64 LIMIT", DisplayName = "Integer64 Limit"))
	static void Int64Limit(int64& Positive, int64& Negative)
	{
		Positive = 9223372036854775807;
		Negative = -9223372036854775807;
	}



	/* Divides A by B and returns the floored value of the result
	Returns an Integer
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (CompactNodeTitle = "//", DisplayName = "Floor Divide (Return Int)"))
	static int32 FloorDivideInt32(float A, float B)
	{
		return (floor((A / B)));
	}
	/* Divides A by B and returns the floored value of the result
	Returns an Integer64
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (CompactNodeTitle = "//", DisplayName = "Floor Divide (Return Int64)"))
	static int64 FloorDivideInt64(double A, double B)
	{
		return (floor((A / B)));
	}



	// Multiplies A by the Power
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (CompactNodeTitle = "**", DisplayName = "Exponentiate (Integer)"))
		static int32 IntToPower(int32 A, int32 Power)
	{
		int32 Result = A;
		for (int i = 1; i < Power; i++)
		{
			Result *= A;
		};
		return Result;
	}
	// Multiplies A by the Power
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (CompactNodeTitle = "**", DisplayName = "Exponentiate (Integer64)"))
		static int64 Int64ToPower(int64 A, int32 Power)
	{
		int64 Result = A;
		for (int i = 1; i < Power; i++)
		{
			Result *= A;
		};
		return Result;
	}
	// Multiplies A by the Power
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (CompactNodeTitle = "**", DisplayName = "Exponentiate (Float)"))
		static double FloatToPower(double A, int32 Power)
	{
		double Result = A;
		for (int i = 1; i < Power; i++)
		{
			Result *= A;
		};
		return Result;
	}



	// Converts a string to a bool
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To Boolean (String)"))
	static bool FStringToBool(FString InString)
	{
		return InString.ToBool();
	}



	// Converts a string Array to a name Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "String Array To Name Array"))
	static void FStringToFName_Array(TArray<FString> InArray, TArray<FName>& ReturnValue)
	{
		TArray<FName> Result;

		for (FString elem : InArray)
		{
			Result.Add(FName(elem));
		};

		ReturnValue = Result;
	}
	// Converts a name Array to a string Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To String Array (Name Array)"))
	static void FNameToFString_Array(TArray<FName> InArray, TArray<FString>& ReturnValue)
	{
		TArray<FString> Result;

		for (FName elem : InArray)
		{
			Result.Add(elem.ToString());
		};

		ReturnValue = Result;
	}
	// Converts a string Array to a text Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| Text", meta = (DisplayName = "To Text Array (String Array)"))
	static void FStringToFText_Array(TArray<FString> InArray, TArray<FText>& ReturnValue)
	{
		TArray<FText> Result;

		for (FString elem : InArray)
		{
			Result.Add(FText::AsCultureInvariant(elem));
		};

		ReturnValue = Result;
	}
	// Converts a text Array to a string Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To String Array (Text Array)"))
	static void FTextToFString_Array(TArray<FText> InArray, TArray<FString>& ReturnValue)
	{
		TArray<FString> Result;

		for (FText elem : InArray)
		{
			Result.Add(elem.ToString());
		};

		ReturnValue = Result;
	}



	// Converts a string Array to a bool Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To Boolean Array (String Array)"))
	static void FStringToBool_Array(TArray<FString> InArray, TArray<bool>& ReturnValue)
	{
		TArray<bool> Result;

		for (FString elem : InArray)
		{
			Result.Add(FStringToBool(elem));
		};

		ReturnValue = Result;
	}
	// Converts a string Array to an int Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "String Array to Integer Array"))
	static void FStringToInt_Array(TArray<FString> InArray, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;
		int32 Out;

		for (FString elem : InArray)
		{
			FDefaultValueHelper::ParseInt(elem, Out);
			Result.Add(Out);
		};

		ReturnValue = Result;
	}
	// Converts a string Array to an int64 Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "String Array to Integer64 Array"))
	static void FStringToInt64_Array(TArray<FString> InArray, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;
		int64 Out;

		for (FString elem : InArray)
		{
			FDefaultValueHelper::ParseInt64(elem, Out);
			Result.Add(Out);
		};

		ReturnValue = Result;
	}
	// Converts a string Array to a float Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "String Array to Float Array"))
	static void FStringToFloat_Array(TArray<FString> InArray, TArray<double>& ReturnValue)
	{
		TArray<double> Result;
		double Out;

		for (FString elem : InArray)
		{
			FDefaultValueHelper::ParseDouble(elem, Out);
			Result.Add(Out);
		};

		ReturnValue = Result;
	}



	// Converts a bool Array to a string Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To String Array (Boolean Array)"))
	static void BoolToFString_Array(TArray<bool> InArray, TArray<FString>& ReturnValue)
	{
		TArray<FString> Result;

		for (bool elem : InArray)
		{
			Result.Add(UKismetStringLibrary::Conv_BoolToString(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int Array to a string Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To String Array (Integer Array)"))
	static void IntToFString_Array(TArray<int32> InArray, TArray<FString>& ReturnValue)
	{
		TArray<FString> Result;

		for (int32 elem : InArray)
		{
			Result.Add(UKismetStringLibrary::Conv_IntToString(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int64 Array to a string Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To String Array (Integer64 Array)"))
	static void Int64ToFString_Array(TArray<int64> InArray, TArray<FString>& ReturnValue)
	{
		TArray<FString> Result;

		for (int64 elem : InArray)
		{
			Result.Add(UKismetStringLibrary::Conv_Int64ToString(elem));
		};

		ReturnValue = Result;
	}
	// Converts a float Array to a string Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (CompactNodeTitle = "->", DisplayName = "To String Array (Float Array)"))
	static void FloatToFString_Array(TArray<double> InArray, TArray<FString>& ReturnValue)
	{
		TArray<FString> Result;

		for (double elem : InArray)
		{
			Result.Add(FString::SanitizeFloat(elem));
		};

		ReturnValue = Result;
	}



	// Converts a bool Array to a text Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| Text", meta = (CompactNodeTitle = "->", DisplayName = "To Text Array (Boolean Array)"))
	static void BoolToFText_Array(TArray<bool> InArray, TArray<FText>& ReturnValue)
	{
		TArray<FText> Result;

		for (bool elem : InArray)
		{
			Result.Add(UKismetTextLibrary::Conv_BoolToText(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int Array to a text Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| Text", meta = (DisplayName = "To Text Array (Integer Array)", AdvancedDisplay = "bAlwaysSign, bUseGrouping, MinumumIntegralDigits, MaximumIntegralDigits"))
	static void IntToFText_Array(TArray<int32> InArray, TArray<FText>& ReturnValue, bool bAlwaysSign = false, bool bUseGrouping = true, int32 MinimumIntegralDigits = 1, int32 MaximumIntegralDigits = 324)
	{
		TArray<FText> Result;

		for (int32 elem : InArray)
		{
			Result.Add(UKismetTextLibrary::Conv_IntToText(elem, bAlwaysSign, bUseGrouping, MinimumIntegralDigits, MaximumIntegralDigits));
		};

		ReturnValue = Result;
	}
	// Converts an int64 Array to a text Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| Text", meta = (DisplayName = "To Text Array (Integer64 Array)", AdvancedDisplay = "bAlwaysSign, bUseGrouping, MinimumIntegralDigits, MaximumIntegralDigits"))
	static void Int64ToFText_Array(TArray<int64> InArray, TArray<FText>& ReturnValue, bool bAlwaysSign = false, bool bUseGrouping = true, int32 MinimumIntegralDigits = 1, int32 MaximumIntegralDigits = 324)
	{
		TArray<FText> Result;

		for (int64 elem : InArray)
		{
			Result.Add(UKismetTextLibrary::Conv_Int64ToText(elem, bAlwaysSign, bUseGrouping, MinimumIntegralDigits, MaximumIntegralDigits));
		};

		ReturnValue = Result;
	}
	// Converts a float Array to a text Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| Text", meta = (DisplayName = "To Text Array (Float Araay)", AdvancedDisplay = "RoundingMode, bAlwaysSign, bUseGrouping, MinimumIntegralDigits, MaximumIntegralDigits, MinimumFractionalDigits, MaximumFractionalDigits"))
	static void FloatToFText_Array(TArray<double> InArray, TArray<FText>& ReturnValue, ERoundingMode RoundingMode = HalfToEven, bool bAlwaysSign = false, bool bUseGrouping = true, int32 MinimumIntegralDigits = 1, int32 MaximumIntegralDigits = 324, int32 MinimumFractionalDigits = 0, int32 MaximumFractionalDigits = 3)
	{
		TArray<FText> Result;

		for (double elem : InArray)
		{
			Result.Add(UKismetTextLibrary::Conv_DoubleToText(elem, RoundingMode, bAlwaysSign, bUseGrouping, MinimumIntegralDigits, MaximumIntegralDigits, MinimumFractionalDigits, MaximumFractionalDigits));
		};
	}



	// Converts an int Array to a bool Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Boolean Array (Integer Array)"))
	static void IntToBool_Array(TArray<int32> InArray, TArray<bool>& ReturnValue)
	{
		TArray<bool> Result;

		for (int32 elem : InArray)
		{
			Result.Add(bool(elem));
		};

		ReturnValue = Result;
	}
	// Converts a bool Array to a byte Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Byte Array (Boolean Array)"))
	static void BoolToUint8_Array(TArray<bool> InArray, TArray<uint8>& ReturnValue)
	{
		TArray<uint8> Result;

		for (bool elem : InArray)
		{
			Result.Add(uint8(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int Array to a byte Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Byte Array (Integer Array)"))
	static void IntToUint8_Array(TArray<int32> InArray, TArray<uint8>& ReturnValue)
	{
		TArray<uint8> Result;

		for (int32 elem : InArray)
		{
			Result.Add(uint8(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int64 Array to a byte Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Byte Array (Integer64 Array)"))
	static void Int64ToUint8_Array(TArray<int64> InArray, TArray<uint8>& ReturnValue)
	{
		TArray<uint8> Result;

		for (int64 Elem : InArray)
		{
			Result.Add(uint8(Elem));
		};

		ReturnValue = Result;
	}
	// Converts a bool Array to a float Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Float Array (Boolean Array)"))
	static void BoolToFloat_Array(TArray<bool> InArray, TArray<float>& ReturnValue)
	{
		TArray<float> Result;

		for (bool elem : InArray)
		{
			Result.Add(float(elem));
		};

		ReturnValue = Result;
	}
	// Converts a byte Array to a float Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Float Array (Byte Array)"))
	static void Uint8ToFloat_Array(TArray<uint8> InArray, TArray<float>& ReturnValue)
	{
		TArray<float> Result;

		for (uint8 elem : InArray)
		{
			Result.Add(float(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int Array to a float Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Float Array (Integer Array)"))
	static void IntToFloat_Array(TArray<int32> InArray, TArray<float>& ReturnValue)
	{
		TArray<float> Result;

		for (int32 elem : InArray)
		{
			Result.Add(float(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int64 Array to a float Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Float Array (Integer64 Array)"))
	static void Int64ToFloat_Array(TArray<int64> InArray, TArray<double>& ReturnValue)
	{
		TArray<double> Result;

		for (int64 elem : InArray)
		{
			Result.Add(double(elem));
		};

		ReturnValue = Result;
	}
	// Converts a bool Array to an int Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Integer Array (Boolean Array)"))
	static void BoolToInt_Array(TArray<bool> InArray, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (bool elem : InArray)
		{
			Result.Add(int32(elem));
		};

		ReturnValue = Result;
	}
	// Converts a byte Array to an int Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Integer Array (Byte Array)"))
	static void Uint8ToInt_Array(TArray<uint8> InArray, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (uint8 elem : InArray)
		{
			Result.Add(int32(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int64 Array to an int Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Integer Array (Integer64 Array)"))
	static void Int64ToInt_Array(TArray<int64> InArray, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (int64 elem : InArray)
		{
			Result.Add(int32(elem));
		};

		ReturnValue = Result;
	}
	// Converts a byte Array to an int64 Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Integer64 Array (Byte Array)"))
	static void Uint8ToInt64_Array(TArray<uint8> InArray, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (uint8 elem : InArray)
		{
			Result.Add(int64(elem));
		};

		ReturnValue = Result;
	}
	// Converts a float Array to an int64 Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Integer64 Array (Float Array)"))
	static void FloatToInt64_Array(TArray<double> InArray, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (float elem : InArray)
		{
			Result.Add(int64(elem));
		};

		ReturnValue = Result;
	}
	// Converts an int Array to an int64 Array
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Integer64 Array (Integer Array)"))
	static void IntToInt64_Array(TArray<int32> InArray, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (int32 elem : InArray)
		{
			Result.Add(int64(elem));
		};

		ReturnValue = Result;
	}



	// Converts a vector to a rotator
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Rotator (Vector)"))
	static FRotator FVectorToFRotator(FVector A)
	{
		FRotator Result;
		Result.Roll = A.X;
		Result.Pitch = A.Y;
		Result.Yaw = A.Z;

		return Result;
	}
	// Converts a rotator to a vector
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Conversions", meta = (CompactNodeTitle = "->", DisplayName = "To Vector (Rotator)"))
	static FVector FRotatorToFVector(FRotator A)
	{
		FVector Result;
		Result.X = A.Roll;
		Result.Y = A.Pitch;
		Result.Z = A.Yaw;

		return Result;
	}



	// Rounds all Array entries to zero, truncating the fractional part (eg., -1.6 becomes -1 and 1.6 becomes 1)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Truncate Array"))
	static void TruncToIntArray(TArray<float> Array, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (float elem : Array)
		{
			Result.Add(FMath::TruncToInt(elem));
		};

		ReturnValue = Result;
	}
	// Rounds all Array entries to zero, truncating the fractional part (eg., -1.6 becomes -1 and 1.6 becomes 1)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Truncate Array to Integer64"))
	static void TruncToInt64Array(TArray<double> Array, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (double elem : Array)
		{
			Result.Add(FMath::TruncToInt64(elem));
		};

		ReturnValue = Result;
	}



	// Rounds all Array entries to the nearest integer (eg., -1.6 becomes -2 and 1.6 becomes 2)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Round Array"))
	static void RoundToIntArray(TArray<float> Array, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (float elem : Array)
		{
			Result.Add(FMath::RoundToInt(elem));
		};

		ReturnValue = Result;
	}
	// Rounds all Array entries to the nearest integer (eg., -1.6 becomes -2 and 1.6 becomes 2)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Round Array to Integer64"))
	static void RoundToInt64Array(TArray<double> Array, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (double elem : Array)
		{
			Result.Add(FMath::RoundToInt64(elem));
		};

		ReturnValue = Result;
	}



	// Rounds all Array entries up to positive infinity / up to the next integer (eg., -1.6 becomes -1 and 1.6 becomes 2)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Ceil Array"))
	static void CeilToIntArray(TArray<float> Array, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (float elem : Array)
		{
			Result.Add(FMath::CeilToInt(elem));
		};

		ReturnValue = Result;
	}
	// Rounds all Array entries up to positive infinity / up to the next integer (eg., -1.6 becomes -1 and 1.6 becomes 2)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Ceil Array to Integer64"))
	static void CeilToInt64Array(TArray<double> Array, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (double elem : Array)
		{
			Result.Add(FMath::CeilToInt64(elem));
		};

		ReturnValue = Result;
	}



	// Rounds all Array entries down to negative infinity / down to the previous integer (eg., -1.6 becomes -1 and 1.6 becomes 2)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Floor Array"))
	static void FloorToIntArray(TArray<float> Array, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (float elem : Array)
		{
			Result.Add(FMath::FloorToInt(elem));
		};

		ReturnValue = Result;
	}
	// Rounds all Array entries down to negative infinity / down to the previous integer (eg., -1.6 becomes -1 and 1.6 becomes 2)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Floor Array to Integer64"))
	static void FloorToInt64Array(TArray<double> Array, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;

		for (double elem : Array)
		{
			Result.Add(FMath::FloorToInt64(elem));
		};

		ReturnValue = Result;
	}



	// Returns true if value at Index is between Min and Max
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "InRangeAtIndex (Integer Array)"))
	static bool InRangeAtIndexInt(TArray<int32> Array, int32 Index, int32 Min, int32 Max = 10, bool InclusiveMin = true, bool InclusiveMax = true)
	{
		int32 Value;
		if (Index <= (Array.Num() - 1))
		{
			Value = Array[Index];
		}
		else
		{
			return false;
		};

		bool bFloorIsGood = false;
		bool bCeilIsGood = false;

		if (InclusiveMin)
		{
			if (Value >= Min)
			{
				bFloorIsGood = true;
			};
		}
		else
		{
			if (Value > Min)
			{
				bFloorIsGood = true;
			};
		};

		if (InclusiveMax)
		{
			if (Value <= Max)
			{
				bCeilIsGood = true;
			}
			else
			{
				if (Value < Max)
				{
					bCeilIsGood = true;
				};
			};
		};

		return (bFloorIsGood && bCeilIsGood);
	}
	// Returns true if value at Index is between Min and Max
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "InRangeAtIndex (Integer64 Array)"))
	static bool InRangeAtIndexInt64(TArray<int64> Array, int32 Index, int64 Min, int64 Max = 10, bool InclusiveMin = true, bool InclusiveMax = true)
	{
		int64 Value;
		if (Index <= (Array.Num() - 1))
		{
			Value = Array[Index];
		}
		else
		{
			return false;
		};

		bool bFloorIsGood = false;
		bool bCeilIsGood = false;

		if (InclusiveMin)
		{
			if (Value >= Min)
			{
				bFloorIsGood = true;
			};
		}
		else
		{
			if (Value > Min)
			{
				bFloorIsGood = true;
			};
		};

		if (InclusiveMax)
		{
			if (Value <= Max)
			{
				bCeilIsGood = true;
			}
			else
			{
				if (Value < Max)
				{
					bCeilIsGood = true;
				};
			};
		};

		return (bFloorIsGood && bCeilIsGood);
	}
	// Returns true if value at Index is between Min and Max
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "InRangeAtIndex (Float Array)"))
	static bool InRangeAtIndexFloat(TArray<double> Array, int32 Index, double Min, double Max = 1.0, bool InclusiveMin = true, bool InclusiveMax = true)
	{
		double Value;
		if (Index <= (Array.Num() - 1))
		{
			Value = Array[Index];
		}
		else
		{
			return false;
		};

		bool bFloorIsGood = false;
		bool bCeilIsGood = false;

		if (InclusiveMin)
		{
			if (Value >= Min)
			{
				bFloorIsGood = true;
			};
		}
		else
		{
			if (Value > Min)
			{
				bFloorIsGood = true;
			};
		};

		if (InclusiveMax)
		{
			if (Value <= Max)
			{
				bCeilIsGood = true;
			}
			else
			{
				if (Value < Max)
				{
					bCeilIsGood = true;
				};
			};
		};

		return (bFloorIsGood && bCeilIsGood);
	}



	/* Returns the percent of an Integer
	@param Rounded If true, rounds the result to the nearest whole number, otherwise truncates the result
	@param Difference The difference between the Value and the Result
	*/
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "Percent Of (Integer)", KeyWords = "%"))
	static void PercentOfInt(int32 Value, int32& ReturnValue, int32& Difference, double Percent = 50.0, bool Rounded = true)
	{
		double PercentRatio = (Percent / 100);
		double PercValue = (float(Value) * PercentRatio);
		int32 Result;

		if (Rounded)
		{
			Result = FMath::RoundToInt32(PercValue);
		}
		else
		{
			Result = FMath::TruncToInt32(PercValue);
		};

		ReturnValue = Result;
		Difference = (Value - Result);
	}
	/* Returns the percent of an Integer64
    @param Rounded If true, rounds the result to the nearest whole number, otherwise truncates the result
	@param Difference The difference between the Value and the Result
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Percent Of (Integer64)", KeyWords = "%"))
	static void PercentOfInt64(int64 Value, int64& ReturnValue, int64& Difference, double Percent = 50.0, bool Rounded = true)
	{
		double PercentRatio = (Percent / 100);
		double PercValue = (double(Value) * PercentRatio);
		int64 Result;

		if (Rounded)
		{
			Result = FMath::RoundToInt64(PercValue);
		}
		else
		{
			Result = FMath::TruncToInt64(PercValue);
		};

		ReturnValue = Result;
		Difference = (Value - Result);
	}
	/* Returns the percent of a Float
	@param Difference The difference between the Value and the Result
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Percent Of (Float)", KeyWords = "%"))
		static void PercentOfFloat(double& ReturnValue, double& Difference, double Value, double Percent = 50.0)
	{
		double PercentRatio = (Percent / 100);
		double Result = (Value * PercentRatio);

		ReturnValue = Result;
		Difference = (Value - Result);
	}



	/* Returns the percent difference between A and B
	@param ForceA If true, forces A as the divisor, otherwise sets the higher value as the divisor
	@param Ratio Percent between 0 and 1
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "Get Percent (Integer)", KeyWords = "%"))
	static void GetPercentInt(int32 A, int32 B, bool ForceA, float& Percent, float& Ratio)
	{
		float Higher;
		float Lower;
		float Result;

		if (ForceA)
		{
			Higher = float(A);
			Lower = float(B);
		}
		else
		{
			if (A > B)
			{
				Higher = float(A);
				Lower = float(B);
			}
			else
			{
				Higher = float(B);
				Lower = float(A);
			};
		};

		Result = (Lower / Higher);

		Percent = (Result * 100);
		Ratio = Result;
	}
	/* Returns the percent difference between A and B
	@param ForceA If true, forces A as the divisor, otherwise sets the higher value as the divisor
    @param Ratio Percent between 0 and 1
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Get Percent (Integer64)", KeyWords = "%"))
	static void GetPercentInt64(int64 A, int64 B, bool ForceA, double& Percent, double& Ratio)
	{
		double Higher;
		double Lower;
		double Result;

		if (ForceA)
		{
			Higher = double(A);
			Lower = double(B);
		}
		else
		{
			if (A > B)
			{
				Higher = double(A);
				Lower = double(B);
			}
			else
			{
				Higher = double(B);
				Lower = double(A);
			};
		};

		Result = (Lower / Higher);

		Percent = (Result * 100);
		Ratio = Result;
	}
	/* Returns the percent difference between A and B
    @param Ratio Percent between 0 and 1
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Get Percent (Float)", KeyWords = "%"))
	static void GetPercentFloat(double A, double B, bool ForceA, double& Percent, double& Ratio)
	{
		double Higher;
		double Lower;
		double Result;

		if (ForceA)
		{
			Higher = A;
			Lower = B;
		}
		else
		{
			if (A > B)
			{
				Higher = A;
				Lower = B;
			}
			else
			{
				Higher = B;
				Lower = A;
			};
		};

		Result = (Lower / Higher);

		Percent = (Result * 100);
		Ratio = Result;
	}



	// Returns average of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Average of float Array"))
	static void AverageFloat(TArray<double> FloatArray, double& AverageValue)
	{
		if (FloatArray.Num() <= 0)
		{
			AverageValue = 0.0;
		}
		else
		{
			double Sum = 0;

			for (double elem : FloatArray)
			{
				Sum += elem;
			};

			AverageValue = (Sum / FloatArray.Num());
		}
	}
	// Returns average of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Average of int64 Array"))
	static void AverageInt64(TArray<int64> Int64_Array, double& AverageValue)
	{
		if (Int64_Array.Num() <= 0)
		{
			AverageValue = 0.0;
		}
		else
		{
			int64 Sum = 0;

			for (int64 elem : Int64_Array)
			{
				Sum += elem;
			};

			AverageValue = (Sum / Int64_Array.Num());
		};
	}



	// Returns mode of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "Mode of int Array"))
	static void ModeInt(TArray<int32> IntArray, int32& ModeValue)
	{
		TArray<FVector2D> vNums;
		FVector2D vNewNum;
		bool bNumExists = false;

		int32 Result = 0;
		int32 HighestFreq = 0;

		FString LMsg = "";

		// Find each value and their frequencies
		for (int32 elem : IntArray)
		{
			for (int i = 0; i < (vNums.Num() - 1); i++)
			{
				if (elem == vNums[i].X)
				{
					vNums[i].Y++;
					bNumExists = true;
					break;
				};
			};
			if (!bNumExists)
			{
				vNewNum.X = elem;
				vNums.Add(vNewNum);
			}
			else
			{
				bNumExists = false;
			};
		};
		// Find value with the highest frequency
		for (FVector2D elem : vNums)
		{
			if (int32(elem.Y) > HighestFreq)
			{
				Result = int32(elem.X);
				HighestFreq = int32(elem.Y);
			};
		};

		ModeValue = Result;
	}
	// Returns mode of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Mode of int64 Array"))
	static void ModeInt64(TArray<int64> Int64_Array, int64& ModeValue)
	{
		TArray<FVector2D> vNums;
		FVector2D vNewNum;
		bool bNumExists = false;

		int64 Result = 0;
		int32 HighestFreq = 0;

		FString LMsg = "";

		// Find each value and their frequencies
		for (int64 elem : Int64_Array)
		{
			for (int i = 0; i < (vNums.Num() - 1); i++)
			{
				if (elem == vNums[i].X)
				{
					vNums[i].Y++;
					bNumExists = true;
					break;
				};
			};
			if (!bNumExists)
			{
				vNewNum.X = elem;
				vNums.Add(vNewNum);
			}
			else
			{
				bNumExists = false;
			};
		};
		// Find value with the highest frequency
		for (FVector2D elem : vNums)
		{
			if (int32(elem.Y) > HighestFreq)
			{
				Result = int64(elem.X);
				HighestFreq = int32(elem.Y);
			};
		};

		ModeValue = Result;
	}
	// Returns mode of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Mode of Float Array"))
	static void ModeFloat(TArray<double> FloatArray, double& ModeValue)
	{
		TArray<FVector2D> vNums;
		FVector2D vNewNum;
		bool bNumExists = false;

		float Result = 0;
		int32 HighestFreq = 0;

		// Find each value and their frequencies
		for (float elem : FloatArray)
		{
			for (int i = 0; i < (vNums.Num() - 1); i++)
			{
				if (elem == vNums[i].X)
				{
					vNums[i].Y++;
					bNumExists = true;
					break;
				};
			};
			if (!bNumExists)
			{
				vNewNum.X = elem;
				vNums.Add(vNewNum);
			}
			else
			{
				bNumExists = false;
			};
		};
		// Find value with the highest frequency
		for (FVector2D elem : vNums)
		{
			if (int32(elem.Y) > HighestFreq)
			{
				Result = elem.X;
				HighestFreq = int32(elem.Y);
			};
		};

		ModeValue = Result;
	}



	// Returns median of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Median of int64 Array"))
	static void MedianInt64(TArray<int64> Int64_Array, double& MedianValue)
	{
		TArray<int64> Sorted; SortArray_Int64(Int64_Array, Sorted);

		if (Sorted.Num() == 0)
		{
			MedianValue = 0.0;
		}
		else
		{
			if (IsEvenInt(Sorted.Num()))
			{
				int32 Index = (floor((Sorted.Num() - 1) / 2));
				int64 Num1 = Sorted[Index];
				int64 Num2 = Sorted[(Index + 1)];

				MedianValue = ((float(Num1) + float(Num2)) / 2);
			}
			else
			{
				int32 Index = (floor((Sorted.Num() - 1) / 2));

				MedianValue = double(Sorted[Index]);
			};
		};
	}
	// Returns median of all array entries. Returns value of 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Median of float Array"))
	static void MedianFloat(TArray<double> FloatArray, double& MedianValue)
	{
		TArray<double> Sorted; SortArray_Float(FloatArray, Sorted);

		if (Sorted.Num() == 0)
		{
			MedianValue = 0.0;
		}
		else
		{
			if (IsEvenInt(Sorted.Num()))
			{
				int32 Index = (floor((Sorted.Num() - 1) / 2));
				float Num1 = Sorted[Index];
				float Num2 = Sorted[(Index + 1)];

				MedianValue = ((Num1 + Num2) / 2);
			}
			else
			{
				int32 Index = (floor((Sorted.Num() - 1) / 2));

				MedianValue = Sorted[Index];
			};
		};
	}



	// Returns midrange of all array entries. Returns 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "MidRange of int Array"))
	static void MidRangeInt(TArray<int32> IntArray, float& MidRangeValue)
	{
		TArray<int32> Sorted; SortArray_Int(IntArray, Sorted);

		if (Sorted.Num() == 0)
		{
			MidRangeValue = 0.0;
		}
		else
		{
			int32 Lowest = Sorted[0];
			int32 Highest = Sorted[(Sorted.Num() - 1)];

			MidRangeValue = ((float(Lowest) + float(Highest)) / 2);
		};
	}
	// Returns midrange of all array entries. Returns 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "MidRange of int64 Array"))
	static void MidRangeInt64(TArray<int64> Int64_Array, double& MidRangeValue)
	{
		TArray<int64> Sorted; SortArray_Int64(Int64_Array, Sorted);

		if (Sorted.Num() == 0)
		{
			MidRangeValue = 0.0;
		}
		else
		{
			int64 Lowest = Sorted[0];
			int64 Highest = Sorted[(Sorted.Num() - 1)];

			MidRangeValue = ((double(Lowest) + double(Highest)) / 2);
		};
	}
	// Returns midrange of all array entries. Returns 0 if the supplied array is empty
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "MidRange of Float Array"))
	static void MidRangeFloat(TArray<double> FloatArray, double& MidRangeValue)
	{
		TArray<double> Sorted; SortArray_Float(FloatArray, Sorted);

		if (Sorted.Num() == 0)
		{
			MidRangeValue = 0.0;
		}
		else
		{
			float Lowest = Sorted[0];
			float Highest = Sorted[(Sorted.Num() - 1)];

			MidRangeValue = ((Lowest + Highest) / 2);
		};
	}



	// Generates a Fibonacci sequence of the given size
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math", meta = (CompactNodeTitle = "FIBONACCI", DisplayName = "Generate Fibonacci Sequence (Integer)"))
	static void GenerateFibonacciSequence32(TArray<int32>& Sequence, int32 Size = 10)
	{
		if (Size >= 1)
		{
			Sequence = { 0 };
		};
		if (Size >= 2)
		{
			Sequence = { 0, 1 };
		};
		if (Size > 2)
		{
			int32 Num1 = 0;
			int32 Num2 = 1;
			int32 ResNum = 1;
			TArray<int32> Result = { 0, 1 };

			for (int i = 2; i <= Size; i++)
			{
				ResNum = (Num1 + Num2);
				Result.Add(ResNum);
				Num1 = Num2;
				Num2 = ResNum;
			};

			Sequence = Result;
		};
	}
	// Generates a Fibonacci sequence of the given size
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math", meta = (CompactNodeTitle = "FIBONACCI", DisplayName = "Generate Fibonacci Sequence (Integer64)"))
	static void GenerateFibonacciSequence64(TArray<int64>& Sequence, int32 Size = 10)
	{
		if (Size >= 1)
		{
			Sequence = { 0 };
		};
		if (Size >= 2)
		{
			Sequence = { 0, 1 };
		};
		if (Size > 2)
		{
			int64 Num1 = 0;
			int64 Num2 = 1;
			int64 ResNum = 1;
			TArray<int64> Result = { 0, 1 };

			for (int i = 2; i <= Size; i++)
			{
				ResNum = (Num1 + Num2);
				Result.Add(ResNum);
				Num1 = Num2;
				Num2 = ResNum;
			};

			Sequence = Result;
		};
	}
	// Multiplies the input value by the Golden Ratio
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Multiply by Golden Ratio"))
	static float TimesGoldenRatio(double Value)
	{
		return (Value * GoldenRatio());
	}


	// Returns true if A is an integral value, otherwise returns false
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "IsIntegral"))
	static bool IsIntegral(double A)
	{
		int64 Chk = FMath::TruncToInt64(A);

		if (A == double(Chk))
		{
			return true;
		}
		else
		{
			return false;
		};
	}




	// Returns true if A is divisible by B, otherwise returns false
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "IsDivisible", KeyWords = "/"))
	static bool IsDivisible(double A, double B)
	{
		double Chk = fmod(A, B);
		
		if (Chk != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}



	// Returns true if A is an even number, otherwise returns false
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "IsEven (Integer)"))
		static bool IsEvenInt(int32 A)
	{
		return IsDivisible(float(A), 2.0);
	}
	// Returns true if A is an even number, otherwise returns false
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "IsEven (Integer64)"))
		static bool IsEvenInt64(int64 A)
	{
		return IsDivisible(double(A), 2.0);
	}



	// Returns true if A is a prime number, otherwise returns false
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "IsPrime (Integer)"))
		static bool IsPrimeInt(int32 A)
	{
		if (A <= 1)
		{
			return false;
		}
		else
		{
			bool bPrime = true;

			for (int i = 2; i <= sqrt(A); i++)
			{
				if (A % i == 0)
				{
					bPrime = false;
					break;
				};
			};
			return bPrime;
		};
	}
	// Returns true if A is a prime number, otherwise returns false
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "IsPrime (Integer64)"))
		static bool IsPrimeInt64(int64 A)
	{
		if (A <= 1)
		{
			return false;
		}
		else
		{
			bool bPrime = true;

			for (int i = 2; i <= sqrt(A); i++)
			{
				if (A % i == 0)
				{
					bPrime = false;
					break;
				};
			};
			return bPrime;
		};
	}



	/* Generates an array of prime numbers in sequence
	@param Size Last index of the generated array
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math", meta = (CompactNodeTitle = "PRIME", DisplayName = "Generate Prime Sequence (Integer)"))
		static void GeneratePrime32(TArray<int32>& Sequence, int32 Size = 10)
	{
		TArray<int32> Result;

		int32 pLimit;
		int32 nLimit;
		IntLimit(pLimit, nLimit);

		for (int32 n = 2; (Result.Num() - 1) < Size || n >= pLimit; n++)
		{
			if (IsPrimeInt(n))
			{
				Result.Add(n);
			};
		};

		Sequence = Result;
	}
	/* Generates an array of prime numbers in sequence
	@param Size Last index of the generated array
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math", meta = (CompactNodeTitle = "PRIME", DisplayName = "Generate Prime Sequence (Integer64)"))
		static void GeneratePrime64(TArray<int64>& Sequence, int32 Size = 10)
	{
		TArray<int64> Result;

		int64 pLimit;
		int64 nLimit;
		Int64Limit(pLimit, nLimit);

		for (int64 n = 2; (Result.Num() - 1) < Size || n >= pLimit; n++)
		{
			if (IsPrimeInt64(n))
			{
				Result.Add(n);
			};
		};

		Sequence = Result;
	}



	/* Returns true if A is a Fibonacci number, otherwise returns false
	@param Scope The size of the Fibonacci Sequence to be generated
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "IsFibonacci (Integer)"))
	static bool IsFibonacci32(int32 A, int32 Scope = 10)
	{
		TArray<int32> Sequence;
		GenerateFibonacciSequence32(Sequence, Scope);

		bool bFibonacci = false;

		for (int32 elem : Sequence)
		{
			if (A == elem)
			{
				bFibonacci = true;
				break;
			};
		};
		return bFibonacci;
	}
	/* Returns true if A is a Fibonacci number, otherwise returns false
    @param Scope The size of the Fibonacci Sequence to be generated
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "IsFibonacci (Integer64)"))
		static bool IsFibonacci64(int64 A, int32 Scope = 10)
	{
		TArray<int64> Sequence;
		GenerateFibonacciSequence64(Sequence, Scope);

		bool bFibonacci = false;

		for (int64 elem : Sequence)
		{
			if (A == elem)
			{
				bFibonacci = true;
				break;
			};
		};
		return bFibonacci;
	}



	/* Splits the array into prime and non-prime numbers
	@param Amount Amount of prime numbers found in the array
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "Get Prime Numbers (Integer Array)"))
	static void GetPrimeNumbersInt(TArray<int32> Array, TArray<int32>& Prime, TArray<int32>& NonPrime, int32& Amount)
	{
		TArray<int32> PrimeResult;
		TArray<int32> NonResult;
		int32 PrimeAmount = 0;

		for (int32 elem : Array)
		{
			if (IsPrimeInt(elem))
			{
				PrimeResult.Add(elem);
				PrimeAmount++;
			}
			else
			{
				NonResult.Add(elem);
			};
		};

		Prime = PrimeResult;
		NonPrime = NonResult;
		Amount = PrimeAmount;
	}
	/* Splits the array into prime and non-prime numbers
    @param Amount Amount of prime numbers found in the array
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Get Prime Numbers (Integer64 Array)"))
	static void GetPrimeNumbersInt64(TArray<int64> Array, TArray<int64>& Prime, TArray<int64>& NonPrime, int32& Amount)
	{
		TArray<int64> PrimeResult;
		TArray<int64> NonResult;
		int32 PrimeAmount = 0;

		for (int64 elem : Array)
		{
			if (IsPrimeInt64(elem))
			{
				PrimeResult.Add(elem);
				PrimeAmount++;
			}
			else
			{
				NonResult.Add(elem);
			};
		};

		Prime = PrimeResult;
		NonPrime = NonResult;
		Amount = PrimeAmount;
	}



	/* Returns the nearest prime number to the value
	@param FavorLower If true, favors the lower prime value, otherwise favors the higher prime value
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "Nearest Prime Number (Integer)"))
	static int32 NearestPrimeInt(int32 A, bool FavorLower)
	{
		int32 Lower = (A - 1);
		int32 Higher = (A + 1);

		if (!IsPrimeInt(A))
		{
			if (FavorLower)
			{
				while (true)
				{
					if (IsPrimeInt(Lower))
					{
						return Lower;
					};

					if (IsPrimeInt(Higher))
					{
						return Higher;
					};

					Lower--;
					Higher++;
				};
			}
			else
			{
				while (true)
				{
					if (IsPrimeInt(Higher))
					{
						return Higher;
					};

					if (IsPrimeInt(Lower))
					{
						return Lower;
					};

					Higher++;
					Lower--;
				};
			};
		}
		else
		{
			return A;
		};
	}
	/* Returns the nearest prime number to the value
	@param FavorLower If true, favors the lower prime value, otherwise favors the higher prime value
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Nearest Prime Number (Integer64)"))
	static int64 NearestPrimeInt64(int64 A, bool FavorLower)
	{
		int64 Lower = (A - 1);
		int64 Higher = (A + 1);

		if (!IsPrimeInt(A))
		{
			if (FavorLower)
			{
				while (true)
				{
					if (IsPrimeInt(Lower))
					{
						return Lower;
					};

					if (IsPrimeInt(Higher))
					{
						return Higher;
					};

					Lower--;
					Higher++;
				};
			}
			else
			{
				while (true)
				{
					if (IsPrimeInt(Higher))
					{
						return Higher;
					};

					if (IsPrimeInt(Lower))
					{
						return Lower;
					};

					Higher++;
					Lower--;
				};
			};
		}
		else
		{
			return A;
		};
	}



	/* Splits the array into integral and non - integral numbers
	@param Amount Amount of integral numbers found in the array
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Get Integral Numbers (Integers)"))
	static void GetIntegralNumbers32(TArray<float> Array, TArray<int32>& Integral, TArray<float>& NonIntegral, int32& Amount)
	{
		TArray<int32> IntegralResult;
		TArray<float> NonResult;
		int32 IntegralAmount = 0;

		for (float elem : Array)
		{
			if (IsIntegral(elem))
			{
				IntegralResult.Add(elem);
				IntegralAmount++;
			}
			else
			{
				NonResult.Add(elem);
			};
		};

		Integral = IntegralResult;
		NonIntegral = NonResult;
		Amount = IntegralAmount;
	}
	/* Splits the array into integral and non - integral numbers
    @param Amount Amount of integral numbers found in the array
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Get Integral Numbers (Integer64s)"))
		static void GetIntegralNumbers64(TArray<double> Array, TArray<int64>& Integral, TArray<double>& NonIntegral, int32& Amount)
	{
		TArray<int64> IntegralResult;
		TArray<double> NonResult;
		int32 IntegralAmount = 0;

		for (double elem : Array)
		{
			if (IsIntegral(elem))
			{
				IntegralResult.Add(elem);
				IntegralAmount++;
			}
			else
			{
				NonResult.Add(elem);
			};
		};

		Integral = IntegralResult;
		NonIntegral = NonResult;
		Amount = IntegralAmount;
	}






	/* Returns an Array of uniformly distributed numbers between 0 and Max - 1
	@param Index Size of the array you want to create
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer Array"))
	static void RandArrayInt(int32 Max, int32 Index, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(FMath::RandRange(0, (Max - 1)));
		};

		ReturnValue = Result;
	}
	/* Returns an Array of uniformly distributed numbers between 0 and Max - 1
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer Array from Stream"))
		static void RandArrayIntFromStream(const FRandomStream& Stream, int32 Max, int32 Index, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(Stream.RandRange(0, (Max - 1)));
		};

		ReturnValue = Result;
	}
	/* Return an Array of random integers between Min and Max (>= Min and <= Max)
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer Array in Range"))
	static void RandArrayIntRange(int32 Min, int32 Max, int32 Index, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(FMath::RandRange(Min, Max));
		};

		ReturnValue = Result;
	}
	/* Return an Array of random integers between Min and Max (>= Min and <= Max)
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer Array in Range from Stream"))
	static void RandArrayIntRangeStream(const FRandomStream& Stream, int32 Min, int32 Max, int32 Index, TArray<int32>& ReturnValue)
	{
		TArray<int32> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(Stream.RandRange(Min, Max));
		};

		ReturnValue = Result;
	}
	/* Returns an Array of uniformly distributed numbers between 0 and Max - 1
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer64 Array"))
	static void RandArrayInt64(int64 Max, int32 Index, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;
		float Temp = 0.0;

		for (int i = 0; i <= Index; i++)
		{
			Temp = FMath::FRandRange(0.0, (double(Max) - 1));
			Result.Add(FMath::TruncToInt64(Temp));
		};

		ReturnValue = Result;
	}
	/* Returns an Array of uniformly distributed numbers between 0 and Max - 1
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer64 Array From Stream"))
	static void RandArrayInt64Stream(const FRandomStream& Stream, int64 Max, int32 Index, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;
		float Temp = 0.0;

		for (int i = 0; i <= Index; i++)
		{
			Temp = Stream.FRandRange(0.0, (double(Max) - 1));
			Result.Add(FMath::TruncToInt64(Temp));
		};

		ReturnValue = Result;
	}
	/* Return an Array of Integer64s between Min and Max (>= Min and <= Max)
    @param Index Size of the array to be created
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer64 Array in Range"))
	static void RandArrayInt64Range(int64 Min, int64 Max, int32 Index, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;
		float Temp = 0.0;

		for (int i = 0; i <= Index; i++)
		{
			Temp = FMath::FRandRange(double(Min), (double(Max) - 1));
			Result.Add(FMath::TruncToInt64(Temp));
		};

		ReturnValue = Result;
	}
	/* Return an Array of Integer64s between Min and Max (>= Min and <= Max)
    @param Index Size of the array to be created
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Integer64 Array in Range from Stream"))
	static void RandArrayInt64RangeStream(FRandomStream Stream, int64 Min, int64 Max, int32 Index, TArray<int64>& ReturnValue)
	{
		TArray<int64> Result;
		float Temp = 0.0;

		for (int i = 0; i <= Index; i++)
		{
			Temp = Stream.FRandRange(double(Min), (double(Max) - 1));
			Result.Add(FMath::TruncToInt64(Temp));
		};

		ReturnValue = Result;
	}



	/* Adds all the values of an Array into a single value
	@param Index The index to add up to
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer", meta = (DisplayName = "Combine Array (Integer)"))
	static void CombineIntArray(TArray<int32> Array, int32 Index, int32& ReturnValue, TArray<int32>& Remaining)
	{
		TArray<int32> Calc = Array;
		int32 Result = 0;
		if (Calc.Num() > 0)

		for (int i = 0; i <= Index && i < Array.Num(); i++)
		{
			Result += Calc[0];
			Calc.RemoveAt(0);
		};

		ReturnValue = Result;
		Remaining = Calc;
	}
	/* Adds all the values of an Array into a single value
    @param Index The index to add up to
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Integer64", meta = (DisplayName = "Combine Array (Integer64)"))
		static void CombineInt64Array(TArray<int64> Array, int32 Index, int64& ReturnValue, TArray<int64>& Remaining)
	{
		TArray<int64> Calc = Array;
		int64 Result = 0;

		for (int i = 0; i <= Index && i < Array.Num(); i++)
		{
			Result += Calc[0];
			Calc.RemoveAt(0);
		};

		ReturnValue = Result;
		Remaining = Calc;
	}
	/* Adds all the values of an Array into a single value
    @param Index The index to add up to
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Float", meta = (DisplayName = "Combine Array (Float)"))
		static void CombineFloatArray(TArray<double> Array, int32 Index, double& ReturnValue, TArray<double>& Remaining)
	{
		TArray<double> Calc = Array;
		double Result = 0;

		for (int i = 0; i <= Index && i < Array.Num(); i++)
		{
			Result += Calc[0];
			Calc.RemoveAt(0);
		};

		ReturnValue = Result;
		Remaining = Calc;
	}
	/* Combines all the strigs in an array into a single string
    @param Index The index to add up to
	@param String added to separate each appended string. Leave empty for no seperator
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities| String", meta = (DisplayName = "Combine Array (String)"))
		static void CombineFStringArray(TArray<FString> Array, int32 Index, FString Separator,  FString& ReturnValue, TArray<FString>& Remaining)
	{
		TArray<FString> Calc = Array;
		FString Result = "";

		for (int i = 0; i <= Index && i < Array.Num(); i++)
		{
			Result += Calc[0];
			Calc.RemoveAt(0);
			if (i < Index)
			{
				Result += Separator;
			};
		};

		ReturnValue = Result;
		Remaining = Calc;
	}
	/* Returns an Array of floats between 0 and 1
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Float Array"))
		static void FRandArray(int32 Index, TArray<double>& ReturnValue)
	{
		TArray<double> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(FMath::FRand());
		};

		ReturnValue = Result;
	}
	/* Returns an Array of floats between 0 and 1
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Float Array from Stream"))
		static void FRandArrayStream(const FRandomStream& Stream, int32 Index, TArray<double>& ReturnValue)
	{
		TArray<double> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(Stream.FRand());
		};

		ReturnValue = Result;
	}
	/* Returns an Array of random numbers between Min and Max (>= Min and <= Max)
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Float Array in Range"))
		static void FRandArrayRange(float Min, float Max, int32 Index, TArray<double>& ReturnValue)
	{
		TArray<double> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(FMath::FRandRange(Min, Max));
		};

		ReturnValue = Result;
	}
	/* Returns an Array of random numbers between Min and Max (>= Min and <= Max)
    @param Index Size of the array you want to create
    */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math| Random", meta = (DisplayName = "Random Float Array in Range from Stream"))
		static void FRandArrayRangeStream(const FRandomStream& Stream, float Min, float Max, int32 Index, TArray<double>& ReturnValue)
	{
		TArray<double> Result;

		for (int i = 0; i <= Index; i++)
		{
			Result.Add(Stream.FRandRange(Min, Max));
		};

		ReturnValue = Result;
	}



protected:
	// An approximation of the Golden Ratio
	UFUNCTION()
	static float GoldenRatio()
	{
		return 1.618;
	}



	// Sorts an array of ints from lowest to highest
	UFUNCTION()
	static void SortArray_Int(TArray<int32> InArray, TArray<int32>& ReturnValue)
	{
		TArray<int32> Calc = InArray;
		int32 Temp;

		for (int i = 0; i < (Calc.Num() - 1); i++)
		{
			for (int j = 0; j < (Calc.Num() - 1); j++)
			{
				if (Calc[j] > Calc[(j + 1)])
				{
					Temp = Calc[j];
					Calc[j] = Calc[(j + 1)];
					Calc[(j + 1)] = Temp;
				};
			};
		};

		ReturnValue = Calc;
	}
	// Sorts an array of int64s from lowest to highest
	UFUNCTION()
	static void SortArray_Int64(TArray<int64> InArray, TArray<int64>& ReturnValue)
	{
		TArray<int64> Calc = InArray;
		int64 Temp;

		for (int i = 0; i < (Calc.Num() - 1); i++)
		{
			for (int j = 0; j < (Calc.Num() - 1); j++)
			{
				if (Calc[j] > Calc[(j + 1)])
				{
					Temp = Calc[j];
					Calc[j] = Calc[(j + 1)];
					Calc[(j + 1)] = Temp;
				};
			};
		};

		ReturnValue = Calc;
	}
	// Sorts an array of floats from lowest to highest
	UFUNCTION()
	static void SortArray_Float(TArray<double> InArray, TArray<double>& ReturnValue)
	{
		TArray<double> Calc = InArray;
		double Temp;

		for (int i = 0; i < (Calc.Num() - 1); i++)
		{
			for (int j = 0; j < (Calc.Num() - 1); j++)
			{
				if (Calc[j] > Calc[(j + 1)])
				{
					Temp = Calc[j];
					Calc[j] = Calc[(j + 1)];
					Calc[(j + 1)] = Temp;
				};
			};
		};

		ReturnValue = Calc;
	}
};

