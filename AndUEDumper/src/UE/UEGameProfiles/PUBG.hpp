#pragma once

#include "../UEGameProfile.hpp"
using namespace UEMemory;

class PUBGProfile : public IGameProfile
{
public:
    PUBGProfile() = default;

    bool ArchSupprted() const override
    {
        auto e_machine = GetUnrealELF().header().e_machine;
        return e_machine == EM_AARCH64;
    }

    std::string GetAppName() const override
    {
        return "和平精英";
    }

    std::vector<std::string> GetAppIDs() const override
    {
        return {"com.tencent.tmgp.pubgmhd"};
    }

    bool isUsingCasePreservingName() const override
    {
        return false;
    }

    bool IsUsingFNamePool() const override
    {
        return false;
    }

    bool isUsingOutlineNumberName() const override
    {
        return false;
    }

    uintptr_t GetGUObjectArrayPtr() const override
    {
        std::string ida_pattern = "? ? ? B9 ? ? ? B9 1F 01 09 6B ? ? ? 54 ? ? ? ? ? ? ? 91 E1 03 14 AA ? ? ? 97 ? ? ? 91 ? ? ? 91";
        const int step = 0x10;

        PATTERN_MAP_TYPE map_type = isEmulator() ? PATTERN_MAP_TYPE::ANY_R : PATTERN_MAP_TYPE::ANY_X;
        //printf("%lx\n", Arm64::Decode_ADRP_ADD(findIdaPattern(map_type, ida_pattern, step)));
        return Arm64::Decode_ADRP_ADD(findIdaPattern(map_type, ida_pattern, step)) + 0xb8;
    }
    void print_func() const
    {
        auto base = GetUEVars()->GetBaseAddress();
        //printf("0x%lx\n", base);
        std::string CalShootTargetLocationBP = "60 1C A3 4E 81 1C A4 4E A2 1C A5 4E C0 03 5F D6 ? ? ? F9";
        std::string DecArray = "? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? 91 ? ? ? D1 ? ? ? B0 ? ? ? F9 F3 03 01 2A F4 03 00 AA ? ? ? B9";
        std::string GetAccessoriesDeviationFactor = "? ? ? BD 81 09 21 1E 00 28 21 1E 40 09 20 1E";
        std::string GetAccessoriesAllRecoilFactorModifier = "40 08 20 1E ? ? ? 71";
        std::string AnimationKick = "0B 08 2B 1E 00 01 3F D6";
        PATTERN_MAP_TYPE map_type = isEmulator() ? PATTERN_MAP_TYPE::ANY_R : PATTERN_MAP_TYPE::ANY_X;
        printf("CalShootTargetLocationBPOffset:0x%lX\n", findIdaPattern(map_type, CalShootTargetLocationBP, 0) - base);
        printf("DecArrayOffset:0x%lX\n", findIdaPattern(map_type, DecArray, 0) - base);
        printf("GetAccessoriesDeviationFactorOffset:0x%lX\n", findIdaPattern(map_type, GetAccessoriesDeviationFactor, 0) - base);
        printf("GetAccessoriesAllRecoilFactorModifierOffset:0x%lX\n", findIdaPattern(map_type, GetAccessoriesAllRecoilFactorModifier, 0) - base);
        printf("AnimationKickOffset:0x%lX\n", findIdaPattern(map_type, AnimationKick, 0) - base);
    }
    uintptr_t GetNamesPtr() const override
    {
        print_func();
        std::string ida_pattern = "? ? ? B0 ? ? ? D0 ? ? ? F9 ? ? ? 91 ? ? ? 91 ? ? ? 94";
        const int step = 0x0;

        PATTERN_MAP_TYPE map_type = isEmulator() ? PATTERN_MAP_TYPE::ANY_R : PATTERN_MAP_TYPE::ANY_X;
        //printf("%lx\n", findIdaPattern(map_type, ida_pattern, step));
        return Arm64::Decode_ADRP_LDR(findIdaPattern(map_type, ida_pattern, step),0x8);
    }

    uintptr_t GetFrameCount() const override
    {
        PATTERN_MAP_TYPE map_type = isEmulator() ? PATTERN_MAP_TYPE::ANY_R : PATTERN_MAP_TYPE::ANY_X;

        std::string ida_pattern = "? ? ? F0 ? ? ? F9 ? ? ? F9 C0 03 5F D6 ? ? ? A9 ? ? ? A9 ? ? ? A9 ? ? ? 91 ? ? ? D1 F3 03 01 2A";
        const int step = 0;
        auto FrameOff = Arm64::Decode_ADRP_LDR(findIdaPattern(map_type, ida_pattern, step));
        if (FrameOff != 0)
            return vm_rpm_ptr<uintptr_t>((void*)FrameOff);
        return 0;
    }

    uintptr_t GetMatrix() const override
    {
        std::vector<std::pair<std::string, int>> idaPatterns = {
            {"? ? ? D0 ? ? ? F9 ? ? ? 32 6B 7D 40 93 6C 25 0A 9B ? ? ? F9 BF 01 08 EB ? ? ? 54 6B 25 0A 9B ? ? ? B9 ? ? ? 31 ? ? ? 54 ? ? ? 14 ? ? ? B4 ? ? ? 32 68 25 08 9B ? ? ? F9 ? ? ? 14", 0},
        };

        PATTERN_MAP_TYPE map_type = isEmulator() ? PATTERN_MAP_TYPE::ANY_R : PATTERN_MAP_TYPE::ANY_X;

        for (const auto& it : idaPatterns)
        {
            std::string ida_pattern = it.first;
            const int step = it.second;

            uintptr_t adrl = Arm64::Decode_ADRP_LDR(findIdaPattern(map_type, ida_pattern, step));
            if (adrl != 0) return adrl;
        }
        return 0;
    }

    uintptr_t GetPhysx() const override
    {
        std::vector<std::pair<std::string, int>> idaPatterns = {
            {"? ? ? B0 00 03 3F D6", 0x0},
        };

        PATTERN_MAP_TYPE map_type = isEmulator() ? PATTERN_MAP_TYPE::ANY_R : PATTERN_MAP_TYPE::ANY_X;

        for (const auto& it : idaPatterns)
        {
            std::string ida_pattern = it.first;
            const int step = it.second;

            uintptr_t adrl = Arm64::Decode_ADRP_LDR(findIdaPattern(map_type, ida_pattern, step),0x20);
            //printf("%lx\n", vm_rpm_ptr<uintptr_t>((void*)adrl));
            if (adrl != 0) return adrl;
        }
        return 0;
    }
    UE_Offsets *GetOffsets() const override
    {
        static UE_Offsets offsets = UE_DefaultOffsets::UE4_18_19(isUsingCasePreservingName());

        static bool once = false;
        if (!once)
        {
            once = true;
            offsets.FNameEntry.Index = sizeof(void *);
            offsets.FNameEntry.Name = sizeof(void *) + sizeof(int32_t);
            offsets.TUObjectArray.NumElements = 0x38;
        }

        return &offsets;
    }
};