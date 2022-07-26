#pragma once

struct BehaviorVarSig
{
    struct Sig
    {
        std::string sigName;
        std::vector<std::string> sigStrings;
        std::vector<std::string> syncBooleanVar;
        std::vector<std::string> syncFloatVar;
        std::vector<std::string> syncIntegerVar;
    };

    //hardcoded
    std::pair<uint64_t, Sig> humanoidSig;
    std::pair<uint64_t, Sig> werewolfSig;
    std::pair<uint64_t, Sig> vampireSig;

    //Sig pool
    std::vector<Sig> sigPool;

    static BehaviorVarSig* Get()
    {
        if (!single)
            single = new BehaviorVarSig();
        return single;
    }

    void initialize()
    {
        const std::string PATH = TiltedPhoques::GetPath().string() + "/behaviors";
        std::vector<std::string> dirs = loadDirs(PATH);
        for (auto item :dirs)
        {
            Sig* sig = loadSigFromDir(item);
            if (sig)
            {
                sigPool.push_back(*sig);
            }
        }
    }

    void patch(BSAnimationGraphManager* apManager, Actor* apActor);

    private:
        static BehaviorVarSig *single;
        Sig* loadSigFromDir(std::string aDir);
        std::vector<std::string> loadDirs(const std::string& acPATH);
};
