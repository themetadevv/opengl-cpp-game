#pragma once


#include <free_type/free_type.h>

namespace Core {
	class FreeTypeLibrary {
	public:
		static inline FT_Library& GetLibrary() {
			static FT_Library ft_library = nullptr;
			if (!ft_library) {
				if(FT_Init_FreeType(&ft_library))
					throw std::runtime_error("Failed to init FreeType");
			}

			return ft_library;
		}

		static inline void Shutdown() {
			FT_Library& lib = FreeTypeLibrary::GetLibrary();
			if (lib) {
				FT_Done_FreeType(lib);
				lib = nullptr;
			}
		}
	};
}