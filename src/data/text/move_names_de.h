const u8 gMoveNames[][13] = {
    [MOVE_NONE] = _("-$$$$$$"),
    [MOVE_POUND] = _("PFUND"),
    [MOVE_KARATE_CHOP] = _("KARATESCHLAG"),
    [MOVE_DOUBLE_SLAP] = _("DUPLEXHIEB"),
    [MOVE_COMET_PUNCH] = _("KOMETENHIEB"),
    [MOVE_MEGA_PUNCH] = _("MEGAHIEB"),
    [MOVE_PAY_DAY] = _("ZAHLTAG"),
    [MOVE_FIRE_PUNCH] = _("FEUERSCHLAG"),
    [MOVE_ICE_PUNCH] = _("EISHIEB"),
    [MOVE_THUNDER_PUNCH] = _("DONNERSCHLAG"),
    [MOVE_SCRATCH] = _("KRATZER"),
    [MOVE_VICE_GRIP] = _("KLAMMER"),
    [MOVE_GUILLOTINE] = _("GUILLOTINE"),
    [MOVE_RAZOR_WIND] = _("KLINGENSTURM"),
    [MOVE_SWORDS_DANCE] = _("SCHWERTTANZ"),
    [MOVE_CUT] = _("ZERSCHNEIDER"),
    [MOVE_GUST] = _("WINDSTOSS"),
    [MOVE_WING_ATTACK] = _("FLÜGELSCHLAG"),
    [MOVE_WHIRLWIND] = _("WIRBELWIND"),
    [MOVE_FLY] = _("FLIEGEN"),
    [MOVE_BIND] = _("KLAMMERGRIFF"),
    [MOVE_SLAM] = _("SLAM"),
    [MOVE_VINE_WHIP] = _("RANKENHIEB"),
    [MOVE_STOMP] = _("STAMPFER"),
    [MOVE_DOUBLE_KICK] = _("DOPPELKICK"),
    [MOVE_MEGA_KICK] = _("MEGAKICK"),
    [MOVE_JUMP_KICK] = _("SPRUNGKICK"),
    [MOVE_ROLLING_KICK] = _("FEGEKICK"),
    [MOVE_SAND_ATTACK] = _("SANDWIRBEL"),
    [MOVE_HEADBUTT] = _("KOPFNUSS"),
    [MOVE_HORN_ATTACK] = _("HORNATTACKE"),
    [MOVE_FURY_ATTACK] = _("FURIENSCHLAG"),
    [MOVE_HORN_DRILL] = _("HORNBOHRER"),
    [MOVE_TACKLE] = _("TACKLE"),
    [MOVE_BODY_SLAM] = _("BODYSLAM"),
    [MOVE_WRAP] = _("WICKEL"),
    [MOVE_TAKE_DOWN] = _("BODYCHECK"),
    [MOVE_THRASH] = _("FUCHTLER"),
    [MOVE_DOUBLE_EDGE] = _("RISIKOTACKLE"),
    [MOVE_TAIL_WHIP] = _("RUTENSCHLAG"),
    [MOVE_POISON_STING] = _("GIFTSTACHEL"),
    [MOVE_TWINEEDLE] = _("DUONADEL"),
    [MOVE_PIN_MISSILE] = _("NADELRAKETE"),
    [MOVE_LEER] = _("SILBERBLICK"),
    [MOVE_BITE] = _("BISS"),
    [MOVE_GROWL] = _("HEULER"),
    [MOVE_ROAR] = _("BRÜLLER"),
    [MOVE_SING] = _("GESANG"),
    [MOVE_SUPERSONIC] = _("SUPERSCHALL"),
    [MOVE_SONIC_BOOM] = _("ULTRASCHALL"),
    [MOVE_DISABLE] = _("AUSSETZER"),
    [MOVE_ACID] = _("SÄURE"),
    [MOVE_EMBER] = _("GLUT"),
    [MOVE_FLAMETHROWER] = _("FLAMMENWURF"),
    [MOVE_MIST] = _("WEISSNEBEL"),
    [MOVE_WATER_GUN] = _("AQUAKNARRE"),
    [MOVE_HYDRO_PUMP] = _("HYDROPUMPE"),
    [MOVE_SURF] = _("SURFER"),
    [MOVE_ICE_BEAM] = _("EISSTRAHL"),
    [MOVE_BLIZZARD] = _("BLIZZARD"),
    [MOVE_PSYBEAM] = _("PSYSTRAHL"),
    [MOVE_BUBBLE_BEAM] = _("BLUBBSTRAHL"),
    [MOVE_AURORA_BEAM] = _("AURORASTRAHL"),
    [MOVE_HYPER_BEAM] = _("HYPERSTRAHL"),
    [MOVE_PECK] = _("SCHNABEL"),
    [MOVE_DRILL_PECK] = _("BOHRSCHNABEL"),
    [MOVE_SUBMISSION] = _("ÜBERROLLER"),
    [MOVE_LOW_KICK] = _("FUSSKICK"),
    [MOVE_COUNTER] = _("KONTER"),
    [MOVE_SEISMIC_TOSS] = _("GEOWURF"),
    [MOVE_STRENGTH] = _("STÄRKE"),
    [MOVE_ABSORB] = _("ABSORBER"),
    [MOVE_MEGA_DRAIN] = _("MEGASAUGER"),
    [MOVE_LEECH_SEED] = _("EGELSAMEN"),
    [MOVE_GROWTH] = _("WACHSTUM"),
    [MOVE_RAZOR_LEAF] = _("RASIERBLATT"),
    [MOVE_SOLAR_BEAM] = _("SOLARSTRAHL"),
    [MOVE_POISON_POWDER] = _("GIFTPUDER"),
    [MOVE_STUN_SPORE] = _("STACHELSPORE"),
    [MOVE_SLEEP_POWDER] = _("SCHLAFPUDER"),
    [MOVE_PETAL_DANCE] = _("BLÄTTERTANZ"),
    [MOVE_STRING_SHOT] = _("FADENSCHUSS"),
    [MOVE_DRAGON_RAGE] = _("DRACHENWUT"),
    [MOVE_FIRE_SPIN] = _("FEUERWIRBEL"),
    [MOVE_THUNDER_SHOCK] = _("DONNERSCHOCK"),
    [MOVE_THUNDERBOLT] = _("DONNERBLITZ"),
    [MOVE_THUNDER_WAVE] = _("DONNERWELLE"),
    [MOVE_THUNDER] = _("DONNER"),
    [MOVE_ROCK_THROW] = _("STEINWURF"),
    [MOVE_EARTHQUAKE] = _("ERDBEBEN"),
    [MOVE_FISSURE] = _("GEOFISSUR"),
    [MOVE_DIG] = _("SCHAUFLER"),
    [MOVE_TOXIC] = _("TOXIN"),
    [MOVE_CONFUSION] = _("KONFUSION"),
    [MOVE_PSYCHIC] = _("PSYCHOKINESE"),
    [MOVE_HYPNOSIS] = _("HYPNOSE"),
    [MOVE_MEDITATE] = _("MEDITATION"),
    [MOVE_AGILITY] = _("AGILITÄT"),
    [MOVE_QUICK_ATTACK] = _("RUCKZUCKHIEB"),
    [MOVE_RAGE] = _("RASEREI"),
    [MOVE_TELEPORT] = _("TELEPORT"),
    [MOVE_NIGHT_SHADE] = _("NACHTNEBEL"),
    [MOVE_MIMIC] = _("MIMIKRY"),
    [MOVE_SCREECH] = _("KREIDESCHREI"),
    [MOVE_DOUBLE_TEAM] = _("DOPPELTEAM"),
    [MOVE_RECOVER] = _("GENESUNG"),
    [MOVE_HARDEN] = _("HÄRTNER"),
    [MOVE_MINIMIZE] = _("KOMPRIMATOR"),
    [MOVE_SMOKESCREEN] = _("RAUCHWOLKE"),
    [MOVE_CONFUSE_RAY] = _("KONFUSTRAHL"),
    [MOVE_WITHDRAW] = _("PANZERSCHUTZ"),
    [MOVE_DEFENSE_CURL] = _("EINIGLER"),
    [MOVE_BARRIER] = _("BARRIERE"),
    [MOVE_LIGHT_SCREEN] = _("LICHTSCHILD"),
    [MOVE_HAZE] = _("DUNKELNEBEL"),
    [MOVE_REFLECT] = _("REFLEKTOR"),
    [MOVE_FOCUS_ENERGY] = _("ENERGIEFOKUS"),
    [MOVE_BIDE] = _("GEDULD"),
    [MOVE_METRONOME] = _("METRONOM"),
    [MOVE_MIRROR_MOVE] = _("SPIEGELTRICK"),
    [MOVE_SELF_DESTRUCT] = _("FINALE"),
    [MOVE_EGG_BOMB] = _("EIERBOMBE"),
    [MOVE_LICK] = _("SCHLECKER"),
    [MOVE_SMOG] = _("SMOG"),
    [MOVE_SLUDGE] = _("SCHLAMMBAD"),
    [MOVE_BONE_CLUB] = _("KNOCHENKEULE"),
    [MOVE_FIRE_BLAST] = _("FEUERSTURM"),
    [MOVE_WATERFALL] = _("KASKADE"),
    [MOVE_CLAMP] = _("SCHNAPPER"),
    [MOVE_SWIFT] = _("STERNSCHAUER"),
    [MOVE_SKULL_BASH] = _("SCHÄDELWUMME"),
    [MOVE_SPIKE_CANNON] = _("DORNKANONE"),
    [MOVE_CONSTRICT] = _("UMKLAMMERUNG"),
    [MOVE_AMNESIA] = _("AMNESIE"),
    [MOVE_KINESIS] = _("PSYKRAFT"),
    [MOVE_SOFT_BOILED] = _("WEICHEI"),
    [MOVE_HI_JUMP_KICK] = _("TURMKICK"),
    [MOVE_GLARE] = _("GIFTBLICK"),
    [MOVE_DREAM_EATER] = _("TRAUMFRESSER"),
    [MOVE_POISON_GAS] = _("GIFTWOLKE"),
    [MOVE_BARRAGE] = _("STAKKATO"),
    [MOVE_LEECH_LIFE] = _("BLUTSAUGER"),
    [MOVE_LOVELY_KISS] = _("TODESKUSS"),
    [MOVE_SKY_ATTACK] = _("HIMMELSFEGER"),
    [MOVE_TRANSFORM] = _("WANDLER"),
    [MOVE_BUBBLE] = _("BLUBBER"),
    [MOVE_DIZZY_PUNCH] = _("IRRSCHLAG"),
    [MOVE_SPORE] = _("PILZSPORE"),
    [MOVE_FLASH] = _("BLITZ"),
    [MOVE_PSYWAVE] = _("PSYWELLE"),
    [MOVE_SPLASH] = _("PLATSCHER"),
    [MOVE_ACID_ARMOR] = _("SÄUREPANZER"),
    [MOVE_CRABHAMMER] = _("KRABBHAMMER"),
    [MOVE_EXPLOSION] = _("EXPLOSION"),
    [MOVE_FURY_SWIPES] = _("KRATZFURIE"),
    [MOVE_BONEMERANG] = _("KNOCHMERANG"),
    [MOVE_REST] = _("ERHOLUNG"),
    [MOVE_ROCK_SLIDE] = _("STEINHAGEL"),
    [MOVE_HYPER_FANG] = _("HYPERZAHN"),
    [MOVE_SHARPEN] = _("SCHÄRFER"),
    [MOVE_CONVERSION] = _("UMWANDLUNG"),
    [MOVE_TRI_ATTACK] = _("TRIPLETTE"),
    [MOVE_SUPER_FANG] = _("SUPERZAHN"),
    [MOVE_SLASH] = _("SCHLITZER"),
    [MOVE_SUBSTITUTE] = _("DELEGATOR"),
    [MOVE_STRUGGLE] = _("VERZWEIFLER"),
    [MOVE_SKETCH] = _("NACHAHMER"),
    [MOVE_TRIPLE_KICK] = _("DREIFACHKICK"),
    [MOVE_THIEF] = _("RAUB"),
    [MOVE_SPIDER_WEB] = _("SPINNENNETZ"),
    [MOVE_MIND_READER] = _("WILLENSLESER"),
    [MOVE_NIGHTMARE] = _("NACHTMAHR"),
    [MOVE_FLAME_WHEEL] = _("FLAMMENRAD"),
    [MOVE_SNORE] = _("SCHNARCHER"),
    [MOVE_CURSE] = _("FLUCH"),
    [MOVE_FLAIL] = _("DRESCHFLEGEL"),
    [MOVE_CONVERSION_2] = _("UMWANDLUNG2"),
    [MOVE_AEROBLAST] = _("LUFTSTOSS"),
    [MOVE_COTTON_SPORE] = _("BAUMWOLLSAAT"),
    [MOVE_REVERSAL] = _("GEGENSCHLAG"),
    [MOVE_SPITE] = _("GROLL"),
    [MOVE_POWDER_SNOW] = _("PULVERSCHNEE"),
    [MOVE_PROTECT] = _("SCHUTZSCHILD"),
    [MOVE_MACH_PUNCH] = _("TEMPOHIEB"),
    [MOVE_SCARY_FACE] = _("GRIMASSE"),
    [MOVE_FAINT_ATTACK] = _("FINTE"),
    [MOVE_SWEET_KISS] = _("BITTERKUSS"),
    [MOVE_BELLY_DRUM] = _("BAUCHTROMMEL"),
    [MOVE_SLUDGE_BOMB] = _("MATSCHBOMBE"),
    [MOVE_MUD_SLAP] = _("LEHMSCHELLE"),
    [MOVE_OCTAZOOKA] = _("OCTAZOOKA"),
    [MOVE_SPIKES] = _("STACHLER"),
    [MOVE_ZAP_CANNON] = _("BLITZKANONE"),
    [MOVE_FORESIGHT] = _("GESICHTE"),
    [MOVE_DESTINY_BOND] = _("ABGANGSBUND"),
    [MOVE_PERISH_SONG] = _("ABGESANG"),
    [MOVE_ICY_WIND] = _("EISSTURM"),
    [MOVE_DETECT] = _("SCANNER"),
    [MOVE_BONE_RUSH] = _("KNOCHENHATZ"),
    [MOVE_LOCK_ON] = _("ZIELSCHUSS"),
    [MOVE_OUTRAGE] = _("WUTANFALL"),
    [MOVE_SANDSTORM] = _("SANDSTURM"),
    [MOVE_GIGA_DRAIN] = _("GIGASAUGER"),
    [MOVE_ENDURE] = _("AUSDAUER"),
    [MOVE_CHARM] = _("CHARME"),
    [MOVE_ROLLOUT] = _("WALZER"),
    [MOVE_FALSE_SWIPE] = _("TRUGSCHLAG"),
    [MOVE_SWAGGER] = _("ANGEBEREI"),
    [MOVE_MILK_DRINK] = _("MILCHGETRÄNK"),
    [MOVE_SPARK] = _("FUNKENSPRUNG"),
    [MOVE_FURY_CUTTER] = _("ZORNKLINGE"),
    [MOVE_STEEL_WING] = _("STAHLFLÜGEL"),
    [MOVE_MEAN_LOOK] = _("HORRORBLICK"),
    [MOVE_ATTRACT] = _("ANZIEHUNG"),
    [MOVE_SLEEP_TALK] = _("SCHLAFREDE"),
    [MOVE_HEAL_BELL] = _("VITALGLOCKE"),
    [MOVE_RETURN] = _("RÜCKKEHR"),
    [MOVE_PRESENT] = _("GESCHENK"),
    [MOVE_FRUSTRATION] = _("FRUSTRATION"),
    [MOVE_SAFEGUARD] = _("BODYGUARD"),
    [MOVE_PAIN_SPLIT] = _("LEIDTEILER"),
    [MOVE_SACRED_FIRE] = _("LÄUTERFEUER"),
    [MOVE_MAGNITUDE] = _("INTENSITÄT"),
    [MOVE_DYNAMIC_PUNCH] = _("WUCHTSCHLAG"),
    [MOVE_MEGAHORN] = _("VIELENDER"),
    [MOVE_DRAGON_BREATH] = _("FEUERODEM"),
    [MOVE_BATON_PASS] = _("STAFFETTE"),
    [MOVE_ENCORE] = _("ZUGABE"),
    [MOVE_PURSUIT] = _("VERFOLGUNG"),
    [MOVE_RAPID_SPIN] = _("TURBODREHER"),
    [MOVE_SWEET_SCENT] = _("LOCKDUFT"),
    [MOVE_IRON_TAIL] = _("EISENSCHWEIF"),
    [MOVE_METAL_CLAW] = _("METALLKLAUE"),
    [MOVE_VITAL_THROW] = _("ÜBERWURF"),
    [MOVE_MORNING_SUN] = _("MORGENGRAUEN"),
    [MOVE_SYNTHESIS] = _("SYNTHESE"),
    [MOVE_MOONLIGHT] = _("MONDSCHEIN"),
    [MOVE_HIDDEN_POWER] = _("KRAFTRESERVE"),
    [MOVE_CROSS_CHOP] = _("KREUZHIEB"),
    [MOVE_TWISTER] = _("WINDHOSE"),
    [MOVE_RAIN_DANCE] = _("REGENTANZ"),
    [MOVE_SUNNY_DAY] = _("SONNENTAG"),
    [MOVE_CRUNCH] = _("KNIRSCHER"),
    [MOVE_MIRROR_COAT] = _("SPIEGELCAPE"),
    [MOVE_PSYCH_UP] = _("PSYCHO-PLUS"),
    [MOVE_EXTREME_SPEED] = _("TURBOTEMPO"),
    [MOVE_ANCIENT_POWER] = _("ANTIK-KRAFT"),
    [MOVE_SHADOW_BALL] = _("SPUKBALL"),
    [MOVE_FUTURE_SIGHT] = _("SEHER"),
    [MOVE_ROCK_SMASH] = _("ZERTRÜMMERER"),
    [MOVE_WHIRLPOOL] = _("WHIRLPOOL"),
    [MOVE_BEAT_UP] = _("PRÜGLER"),
    [MOVE_FAKE_OUT] = _("MOGELHIEB"),
    [MOVE_UPROAR] = _("AUFRUHR"),
    [MOVE_STOCKPILE] = _("HORTER"),
    [MOVE_SPIT_UP] = _("ENTFESSLER"),
    [MOVE_SWALLOW] = _("VERZEHRER"),
    [MOVE_HEAT_WAVE] = _("HITZEWELLE"),
    [MOVE_HAIL] = _("HAGELSTURM"),
    [MOVE_TORMENT] = _("FOLTERKNECHT"),
    [MOVE_FLATTER] = _("SCHMEICHLER"),
    [MOVE_WILL_O_WISP] = _("IRRLICHT"),
    [MOVE_MEMENTO] = _("MEMENTO-MORI"),
    [MOVE_FACADE] = _("FASSADE"),
    [MOVE_FOCUS_PUNCH] = _("POWER-PUNCH"),
    [MOVE_SMELLING_SALT] = _("RIECHSALZ"),
    [MOVE_FOLLOW_ME] = _("SPOTLIGHT"),
    [MOVE_NATURE_POWER] = _("NATUR-KRAFT"),
    [MOVE_CHARGE] = _("LADEVORGANG"),
    [MOVE_TAUNT] = _("VERHÖHNER"),
    [MOVE_HELPING_HAND] = _("RECHTE HAND"),
    [MOVE_TRICK] = _("TRICKBETRUG"),
    [MOVE_ROLE_PLAY] = _("ROLLENTAUSCH"),
    [MOVE_WISH] = _("WUNSCHTRAUM"),
    [MOVE_ASSIST] = _("ZUSCHUSS"),
    [MOVE_INGRAIN] = _("VERWURZLER"),
    [MOVE_SUPERPOWER] = _("KRAFTKOLOSS"),
    [MOVE_MAGIC_COAT] = _("MAGIEMANTEL"),
    [MOVE_RECYCLE] = _("AUFBEREITUNG"),
    [MOVE_REVENGE] = _("VERGELTUNG"),
    [MOVE_BRICK_BREAK] = _("DURCHBRUCH"),
    [MOVE_YAWN] = _("GÄHNER"),
    [MOVE_KNOCK_OFF] = _("ABSCHLAG"),
    [MOVE_ENDEAVOR] = _("NOTSITUATION"),
    [MOVE_ERUPTION] = _("ERUPTION"),
    [MOVE_SKILL_SWAP] = _("WERTEWECHSEL"),
    [MOVE_IMPRISON] = _("BEGRENZER"),
    [MOVE_REFRESH] = _("HEILUNG"),
    [MOVE_GRUDGE] = _("NACHSPIEL"),
    [MOVE_SNATCH] = _("ÜBERNAHME"),
    [MOVE_SECRET_POWER] = _("GEHEIMPOWER"),
    [MOVE_DIVE] = _("TAUCHER"),
    [MOVE_ARM_THRUST] = _("ARMSTOSS"),
    [MOVE_CAMOUFLAGE] = _("TARNUNG"),
    [MOVE_TAIL_GLOW] = _("SCHWEIFGLANZ"),
    [MOVE_LUSTER_PURGE] = _("SCHEINWERFER"),
    [MOVE_MIST_BALL] = _("NEBELBALL"),
    [MOVE_FEATHER_DANCE] = _("DAUNENREIGEN"),
    [MOVE_TEETER_DANCE] = _("TAUMELTANZ"),
    [MOVE_BLAZE_KICK] = _("FEUERFEGER"),
    [MOVE_MUD_SPORT] = _("LEHMSUHLER"),
    [MOVE_ICE_BALL] = _("FROSTBEULE"),
    [MOVE_NEEDLE_ARM] = _("NIETENRANKE"),
    [MOVE_SLACK_OFF] = _("TAGEDIEB"),
    [MOVE_HYPER_VOICE] = _("SCHALLWELLE"),
    [MOVE_POISON_FANG] = _("GIFTZAHN"),
    [MOVE_CRUSH_CLAW] = _("ZERMALMKLAUE"),
    [MOVE_BLAST_BURN] = _("LOHEKANONADE"),
    [MOVE_HYDRO_CANNON] = _("AQUAHAUBITZE"),
    [MOVE_METEOR_MASH] = _("STERNENHIEB"),
    [MOVE_ASTONISH] = _("ERSTAUNER"),
    [MOVE_WEATHER_BALL] = _("METEOROLOGE"),
    [MOVE_AROMATHERAPY] = _("AROMAKUR"),
    [MOVE_FAKE_TEARS] = _("TRUGTRÄNE"),
    [MOVE_AIR_CUTTER] = _("WINDSCHNITT"),
    [MOVE_OVERHEAT] = _("HITZEKOLLER"),
    [MOVE_ODOR_SLEUTH] = _("SCHNÜFFLER"),
    [MOVE_ROCK_TOMB] = _("FELSGRAB"),
    [MOVE_SILVER_WIND] = _("SILBERHAUCH"),
    [MOVE_METAL_SOUND] = _("METALLSOUND"),
    [MOVE_GRASS_WHISTLE] = _("GRASFLÖTE"),
    [MOVE_TICKLE] = _("SPASSKANONE"),
    [MOVE_COSMIC_POWER] = _("KOSMIK-KRAFT"),
    [MOVE_WATER_SPOUT] = _("FONTRÄNEN"),
    [MOVE_SIGNAL_BEAM] = _("AMPELLEUCHTE"),
    [MOVE_SHADOW_PUNCH] = _("FINSTERFAUST"),
    [MOVE_EXTRASENSORY] = _("SONDERSENSOR"),
    [MOVE_SKY_UPPERCUT] = _("HIMMELHIEB"),
    [MOVE_SAND_TOMB] = _("SANDGRAB"),
    [MOVE_SHEER_COLD] = _("EISESKÄLTE"),
    [MOVE_MUDDY_WATER] = _("LEHMBRÜHE"),
    [MOVE_BULLET_SEED] = _("KUGELSAAT"),
    [MOVE_AERIAL_ACE] = _("AERO-ASS"),
    [MOVE_ICICLE_SPEAR] = _("EISSPEER"),
    [MOVE_IRON_DEFENSE] = _("EISENABWEHR"),
    [MOVE_BLOCK] = _("RÜCKENTZUG"),
    [MOVE_HOWL] = _("JAULER"),
    [MOVE_DRAGON_CLAW] = _("DRACHENKLAUE"),
    [MOVE_FRENZY_PLANT] = _("FAUNA-STATUE"),
    [MOVE_BULK_UP] = _("PROTZER"),
    [MOVE_BOUNCE] = _("SPRUNGFEDER"),
    [MOVE_MUD_SHOT] = _("LEHMSCHUSS"),
    [MOVE_POISON_TAIL] = _("GIFTSCHWEIF"),
    [MOVE_COVET] = _("BEZIRZER"),
    [MOVE_VOLT_TACKLE] = _("VOLTTACKLE"),
    [MOVE_MAGICAL_LEAF] = _("ZAUBERBLATT"),
    [MOVE_WATER_SPORT] = _("NASSMACHER"),
    [MOVE_CALM_MIND] = _("GEDANKENGUT"),
    [MOVE_LEAF_BLADE] = _("LAUBKLINGE"),
    [MOVE_DRAGON_DANCE] = _("DRACHENTANZ"),
    [MOVE_ROCK_BLAST] = _("FELSWURF"),
    [MOVE_SHOCK_WAVE] = _("SCHOCKWELLE"),
    [MOVE_WATER_PULSE] = _("AQUAWELLE"),
    [MOVE_DOOM_DESIRE] = _("KISMETWUNSCH"),
    [MOVE_PSYCHO_BOOST] = _("PSYSCHUB"),
    // later gens
    // gen 4
    [MOVE_AIR_SLASH] = _("AIR SLASH"),
    [MOVE_AQUA_JET] = _("AQUA JET"),
    [MOVE_AQUA_TAIL] = _("AQUA TAIL"),
    [MOVE_ASSURANCE] = _("ASSURANCE"),
    [MOVE_AURA_SPHERE] = _("AURA SPHERE"),
    [MOVE_AVALANCHE] = _("AVALANCHE"),
    [MOVE_BRAVE_BIRD] = _("BRAVE BIRD"),
    [MOVE_BRINE] = _("BRINE"),
    [MOVE_BUG_BITE] = _("BUG BITE"),
    [MOVE_BUG_BUZZ] = _("BUG BUZZ"),
    [MOVE_BULLET_PUNCH] = _("BULLET PUNCH"),
    [MOVE_CAPTIVATE] = _("CAPTIVATE"),
    [MOVE_CHARGE_BEAM] = _("CHARGE BEAM"),
    [MOVE_CLOSE_COMBAT] =  _("CLOSE COMBAT"),
    [MOVE_CROSS_POISON] = _("CROSS POISON"),
    [MOVE_CRUSH_GRIP] = _("CRUSH GRIP"),
    [MOVE_DARK_PULSE] = _("DARK PULSE"),
    [MOVE_DEFOG] = _("DEFOG"),
    [MOVE_DISCHARGE] = _("DISCHARGE"),
    [MOVE_DOUBLE_HIT] = _("DOUBLE HIT"),
    [MOVE_DRACO_METEOR] = _("DRACO METEOR"),
    [MOVE_DRAGON_PULSE] = _("DRAGON PULSE"),
    [MOVE_DRAGON_RUSH] = _("DRAGON RUSH"),
    [MOVE_DRAIN_PUNCH] = _("DRAIN PUNCH"),
    [MOVE_EARTH_POWER] = _("EARTH POWER"),
    [MOVE_ENERGY_BALL] = _("ENERGY BALL"),
    [MOVE_FEINT] = _("FEINT"),
    [MOVE_FIRE_FANG] = _("FIRE FANG"),
    [MOVE_FLARE_BLITZ] = _("FLARE BLITZ"),
    [MOVE_FLASH_CANNON] = _("FLASH CANNON"),
    [MOVE_FOCUS_BLAST] = _("FOCUS BLAST"),
    [MOVE_FORCE_PALM] = _("FORCE PALM"),
    [MOVE_GIGA_IMPACT] = _("GIGA IMPACT"),
    [MOVE_GRASS_KNOT] = _("GRASS KNOT"),
    [MOVE_GUARD_SWAP] = _("GUARD SWAP"),
    [MOVE_GUNK_SHOT] = _("GUNK SHOT"),
    [MOVE_GYRO_BALL] = _("GYRO BALL"),
    [MOVE_HAMMER_ARM] = _("HAMMER ARM"),
    [MOVE_HEAD_SMASH] = _("HEAD SMASH"),
    [MOVE_HEART_SWAP] = _("HEART SWAP"),
    [MOVE_ICE_FANG] = _("ICE FANG"),
    [MOVE_ICE_SHARD] = _("ICE SHARD"),
    [MOVE_IRON_HEAD] = _("IRON HEAD"),
    [MOVE_LAVA_PLUME] = _("LAVA PLUME"),
    [MOVE_LEAF_STORM] = _("LEAF STORM"),
    [MOVE_LUCKY_CHANT] = _("LUCKY CHANT"),
    [MOVE_MAGNET_BOMB] = _("MAGNET BOMB"),
    [MOVE_MIRROR_SHOT] = _("MIRROR SHOT"),
    [MOVE_MUD_BOMB] = _("MUD BOMB"),
    [MOVE_NASTY_PLOT] = _("NASTY PLOT"),
    [MOVE_NIGHT_SLASH] = _("NIGHT SLASH"),
    [MOVE_OMINOUS_WIND] = _("OMINOUS WIND"),
    [MOVE_XSCISSOR] = _("X-SCISSOR"),
    // new moves
};
