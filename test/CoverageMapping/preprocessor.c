// RUN: %clang_cc1 -fprofile-instrument=clang -fcoverage-mapping -dump-coverage-mapping -emit-llvm-only -main-file-name preprocessor.c %s | FileCheck %s

                 // CHECK: func
void func() {    // CHECK: File 0, [[@LINE]]:13 -> [[@LINE+5]]:2 = #0
  int i = 0;
#ifdef MACRO     // CHECK-NEXT: Skipped,File 0, [[@LINE]]:1 -> [[@LINE+3]]:1 = 0
  int x = i;
#endif
}

                 // CHECK: main
int main() {     // CHECK-NEXT: File 0, [[@LINE]]:12 -> {{[0-9]+}}:2 = #0
  int i = 0;
#  if 0            // CHECK-NEXT: Skipped,File 0, [[@LINE]]:1 -> [[@LINE+5]]:1 = 0
  if(i == 0) {
    i = 1;
  }
#  endif // Mark me skipped!

#if 1
                 // CHECK-NEXT: File 0, [[@LINE+1]]:6 -> [[@LINE+1]]:12 = #0
  if(i == 0) {   // CHECK: File 0, [[@LINE]]:14 -> [[@LINE+2]]:4 = #1
    i = 1;
  }
#else            // CHECK-NEXT: Skipped,File 0, [[@LINE]]:1 -> [[@LINE+6]]:1 = 0
  if(i == 1) {
    i = 0;
  }
}
#endif

  // CHECK-NEXT: Skipped,File 0, [[@LINE+1]]:1 -> [[@LINE+5]]:1
#\
  if 0
#\
  endif // also skipped

#if 1
  // CHECK-NEXT: Skipped,File 0, [[@LINE+1]]:1 -> [[@LINE+4]]:1
#\
  elif 0
#endif

#if 1
  // CHECK-NEXT: Skipped,File 0, [[@LINE+1]]:1 -> [[@LINE+4]]:1
#\
  else
#endif

  // CHECK-NEXT: Skipped,File 0, [[@LINE+1]]:1 -> [[@LINE+5]]:1
#\
  ifdef NOT_DEFINED
#\
  endif

  // CHECK-NEXT: Skipped,File 0, [[@LINE+1]]:1 -> [[@LINE+5]]:1
#\
  ifndef __FILE__
#\
  endif

  // CHECK-NEXT: Skipped,File 0, [[@LINE+1]]:1 -> [[@LINE+7]]:1
#\
  ifdef NOT_DEFINED
#\
  \
   \
    endif // also skipped

  return 0;
}
