static char help[] = "Solves a standard eigensystem Ax=kx with the matrix loaded from a file.\n"
  "This example works for both real and complex numbers.\n\n"
  "The command line options are:\n"
  "  -file <filename>, where <filename> = matrix file in PETSc binary form.\n\n";

#include "petscmat.h"
#include "petscvec.h"
#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

#define max(a, b)       ((a) > (b) ? (a) : (b))
#define min(a, b)       ((a) < (b) ? (a) : (b))



typedef struct {
  uint32_t minParticles, maxParticles, nParticles;
  double minEnergy, maxEnergy, energyBinWidth;
  uint32_t nEnergy;
  double volume;
  uint32_t outer_cols, outer_rows, inner_cols, inner_rows;
} parq_info;


#undef __FUNCT__
#define __FUNCT__ "fakult"
double fakult(int eingabe)
{
   if(eingabe<=1) return 1.0;   // da fak(0) gleich 1 ist und fak(1) ebenfalls 1 ist
   double ergebnis=1.0;
   do
   {
      ergebnis = ergebnis * eingabe;
      eingabe--;
   }while(eingabe>1);
   return ergebnis;
}

#undef __FUNCT__
#define __FUNCT__ "vec_get_dist"
void vec_get_dist(Vec x,Vec y,PetscReal *max, PetscInt *max_elem) {
  PetscInt x_local_rows, y_local_rows, x_start_row, x_end_row, y_start_row, y_end_row, i;
  VecGetLocalSize(x,&x_local_rows);
  VecGetLocalSize(y,&y_local_rows);
  VecGetOwnershipRange(x, &x_start_row, &x_end_row);
  VecGetOwnershipRange(y, &y_start_row, &y_end_row);
  PetscScalar *xa, *ya;
  if(x_local_rows != y_local_rows || x_start_row != y_start_row || x_start_row != y_start_row) {
    (*PetscErrorPrintf)("Error! Local vectors do not have equal settings: %d %d | %d %d | %d %d\n", x_local_rows, y_local_rows, x_start_row, y_start_row, x_start_row, y_start_row);
  }
  VecGetArray(x,&xa);
  VecGetArray(y,&ya);
  for(i = 0; i < x_local_rows; ++i) {
    __builtin_prefetch(xa+i+1,1);
    __builtin_prefetch(ya+i+1,0);
    if(xa[i] > 0) {
      xa[i] = fabs(ya[i]/xa[i]-1);
    } else {
      xa[i] = 0;
    }
  }
  VecRestoreArray(x, &xa);
  VecRestoreArray(y, &ya);
  VecMax(x, max_elem, max);
  //PetscPrintf(PETSC_COMM_WORLD,"distance: %g %d\n", *max, *max_elem);
}

#undef __FUNCT__
#define __FUNCT__ "fprintf_dos_file"
PetscErrorCode fprintf_dos_file(FILE* file, PetscInt n, PetscReal energy, PetscReal value, PetscReal fakln) {
  PetscErrorCode ierr;
  PetscFunctionBegin;
  ierr = PetscSynchronizedFPrintf(PETSC_COMM_WORLD, file, "%4d %12g %20.12g %20.12g %20.12g\n", n, energy, log(value) + fakln, log(value), value);CHKERRQ(ierr);
  PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ "fprintf_err_file"
PetscErrorCode fprintf_err_file(FILE* file, PetscInt n, PetscReal energy, PetscReal value, PetscReal fakln) {
  PetscErrorCode ierr;
  PetscFunctionBegin;
  ierr = PetscSynchronizedFPrintf(PETSC_COMM_WORLD, file, "%4d %12g %20.12g\n", n, energy, value);CHKERRQ(ierr);
  PetscFunctionReturn(0);
}

typedef PetscErrorCode(*formatting_func)(FILE*, PetscInt, PetscReal, PetscReal, PetscReal);

#undef __FUNCT__
#define __FUNCT__ "vec_to_file"
PetscErrorCode vec_to_file(Vec u, PetscInt iteration, PetscReal dist, const char *prefix, parq_info *info) {
  PetscInt       lrows, start_row, end_row, nEnergy, i, n, j;
  PetscInt       rank;
  PetscScalar    *v0a;
  PetscReal      fak, fakln, value;
  FILE *         file;
  char filename[100];
  formatting_func ffunc;
  PetscErrorCode ierr;
  PetscFunctionBegin;

  MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  VecGetLocalSize(u,&lrows);
  VecGetOwnershipRange(u, &start_row, &end_row);
  VecGetArray(u,&v0a);
  if(prefix == NULL) {
    PetscSNPrintf(filename, 100, "%s.%06d_%.6g.dat", "pet", iteration, dist);
    ffunc = &fprintf_dos_file;
  } else {
    PetscSNPrintf(filename, 100, "%s.%06d_%.6g.dat", prefix, iteration, dist);
    ffunc = &fprintf_err_file;
  }
  
  ierr = PetscFOpen(PETSC_COMM_WORLD, filename, "w", &file);CHKERRQ(ierr);
  if(!rank) {
    // print a comment line to invoke fprintf at lease once on the first processor
    ierr = PetscSynchronizedFPrintf(PETSC_COMM_WORLD, file, "#\n");CHKERRQ(ierr);
  }
  fak = 1.0;
  nEnergy = info->nEnergy;
  for(i = 0; i < lrows; ++i) {
    n = (start_row+i)/(double)nEnergy+2;
    j = (start_row+i)-((n-2)*nEnergy);
    fakln = 0.0;
    if(n > 0) {
      fak = fakult(n);
      fakln = n*log(125.0)-log(fak);
    }
    value = v0a[i];
    if(value > 0) {
      ierr = (*ffunc)(file, n, (j*(info->maxEnergy-info->minEnergy)/(double)(nEnergy)+info->minEnergy)+(info->energyBinWidth/2), value, fakln);
    }
  }
  PetscSynchronizedFlush(PETSC_COMM_WORLD);
  PetscFClose(PETSC_COMM_WORLD, file);
  VecRestoreArray(u, &v0a);
  PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ "read_parq_matrix"
PetscErrorCode read_parq_matrix(const char * filename, Mat *A, parq_info *info) {
  gzFile pf;
  int i,j,ni,nj;
  PetscInt m,n, rank;
  double *data;
  PetscErrorCode ierr;
  PetscFunctionBegin;
  
  MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  
  if(!rank) {
    pf = gzopen(filename, "rb");
    
    gzread(pf, (char*)&(info->minParticles),   sizeof(info->minParticles));
    gzread(pf, (char*)&(info->maxParticles),   sizeof(info->maxParticles));
    gzread(pf, (char*)&(info->nParticles),     sizeof(info->nParticles));
    gzread(pf, (char*)&(info->minEnergy),      sizeof(info->minEnergy));
    gzread(pf, (char*)&(info->maxEnergy),      sizeof(info->maxEnergy));
    gzread(pf, (char*)&(info->energyBinWidth), sizeof(info->energyBinWidth));
    gzread(pf, (char*)&(info->nEnergy),        sizeof(info->nEnergy));
    gzread(pf, (char*)&(info->volume),         sizeof(info->volume));
    gzread(pf, (char*)&(info->outer_cols),     sizeof(info->outer_cols));
    gzread(pf, (char*)&(info->outer_rows),     sizeof(info->outer_rows));
    gzread(pf, (char*)&(info->inner_cols),     sizeof(info->inner_cols));
    gzread(pf, (char*)&(info->inner_rows),     sizeof(info->inner_rows));
  }
  MPI_Bcast(info, sizeof(parq_info), MPI_CHAR, 0, PETSC_COMM_WORLD);
  // create Matrix
  ierr = MatCreateMPIAIJ(PETSC_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,info->outer_rows*info->inner_rows,info->outer_cols*info->inner_cols,500,PETSC_NULL,500,PETSC_NULL,A);
  //ierr = MatCreateSeqAIJ(PETSC_COMM_WORLD,info->outer_rows*info->inner_rows,info->outer_cols*info->inner_cols,1000,0,A);CHKERRQ(ierr);
  //ierr = MatSetOption(*A, MAT_USE_HASH_TABLE, PETSC_TRUE);CHKERRQ(ierr);
  data = malloc(sizeof(double)*info->inner_rows*info->inner_cols);
  
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Matrix Informationen:\nSize: %d*%d X %d*%d\n", info->outer_rows, info->inner_rows, info->outer_cols, info->inner_cols);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"System:\n  Particles: %d - %d | %d\n", info->minParticles, info->maxParticles, info->nParticles);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"  Energy   : %f - %f | %d | %f\n", info->minEnergy, info->maxEnergy, info->nEnergy, info->energyBinWidth);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"  Volume   : %f\n", info->volume);CHKERRQ(ierr);
  
  if(!rank) {
    for (ni = 0; ni < (int)(info->outer_cols); ++ni) {
      for (nj = max(ni-1, 0);
           nj < min(ni+2, (int)(info->outer_rows));
           ++nj)
      {
        if(!rank) {
          gzread(pf, (char*)data, sizeof(double)*info->inner_rows*info->inner_cols);
        }
        for(i = 0; i < info->inner_rows; ++i) {
          for(j = 0; j < info->inner_cols; ++j)
          {
            if(data[i*info->inner_rows+j] > 0) {
              m = info->inner_rows*nj+j;
              n = info->inner_cols*ni+i;
              ierr = MatSetValue(*A,n,m,(data[i*info->inner_rows+j]),INSERT_VALUES);CHKERRQ(ierr);
            }
          }
        }
      }
    }
  }
  ierr = MatAssemblyBegin(*A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  ierr = MatAssemblyEnd(*A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  free(data);
  if(!rank) {
    gzclose(pf);
  }
  PetscFunctionReturn(0);
}

/**
 * own normalization function that does norm1 with real division and not
 * by reciprocal multiplication
 * input y
 * output x
 * ouput ret_norm
 */
#undef __FUNCT__
#define __FUNCT__ "power_norm"
PetscErrorCode power_norm(Vec x, Vec y, PetscReal *ret_norm) {
  PetscErrorCode ierr;
  PetscFunctionBegin;
  PetscInt x_local_rows, y_local_rows, x_start_row, x_end_row, y_start_row, y_end_row, i;
  PetscReal norm, all_norm;
  ierr = VecGetLocalSize(x,&x_local_rows);CHKERRQ(ierr);
  ierr = VecGetLocalSize(y,&y_local_rows);CHKERRQ(ierr);
  ierr = VecGetOwnershipRange(x, &x_start_row, &x_end_row);CHKERRQ(ierr);
  ierr = VecGetOwnershipRange(y, &y_start_row, &y_end_row);CHKERRQ(ierr);
  PetscScalar *xa, *ya;
  if(x_local_rows != y_local_rows || x_start_row != y_start_row || x_start_row != y_start_row) {
    (*PetscErrorPrintf)("Error! Local vectors do not have equal settings: %d %d | %d %d | %d %d\n", x_local_rows, y_local_rows, x_start_row, y_start_row, x_start_row, y_start_row);
  }
  ierr = VecGetArray(x,&xa);CHKERRQ(ierr);
  ierr = VecGetArray(y,&ya);CHKERRQ(ierr);
  norm = 0;
  for(i = 0; i < y_local_rows; ++i) {
    __builtin_prefetch(ya+i+1,0);
    norm += ya[i];
  }
  //ierr = PetscSynchronizedPrintf(PETSC_COMM_WORLD,"norm: %g\n", norm);CHKERRQ(ierr);
  //PetscSynchronizedFlush(PETSC_COMM_WORLD);
  MPI_Allreduce(&norm, &all_norm, 1, MPI_DOUBLE, MPI_SUM, PETSC_COMM_WORLD);
  //ierr = PetscSynchronizedPrintf(PETSC_COMM_WORLD,"all_norm: %g\n", norm);CHKERRQ(ierr);
  //PetscSynchronizedFlush(PETSC_COMM_WORLD);
  norm = all_norm;
  for(i = 0; i < y_local_rows; ++i) {
    __builtin_prefetch(xa+i+1,1);
    __builtin_prefetch(ya+i+1,0);
    xa[i] = ya[i] / norm;
  }
  ierr = VecRestoreArray(x, &xa);CHKERRQ(ierr);
  ierr = VecRestoreArray(y, &ya);CHKERRQ(ierr);
  *ret_norm = norm;
  PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ "main"
int main( int argc, char **argv )
{
  Vec            x,b,u,d;      /* approx solution, RHS, exact solution */
  Mat            A;            /* linear system matrix */
  PetscErrorCode ierr;
  char        	 filename[256];
  //PetscViewer 	 viewer;
  PetscTruth  	 flg;
  PetscInt       i,/*j,*/cols, rows, /*n, nEnergy, */lcols, lrows, /*start_row, end_row, */plot_every, max_iter,rank, dist_elem, size;
  PetscReal      norm, /*fak, fakln, value,*/ dist;
  PetscScalar    lambda, residual/*, *v0a*/;
  PetscLogDouble v1,v2;
  MatInfo        info;
  parq_info      pq_info;

  PetscInitialize(&argc,&argv,(char *)0,help);

  //ierr = PetscPrintf(PETSC_COMM_WORLD,"\nEigenproblem stored in file.\n\n");CHKERRQ(ierr);
  ierr = PetscOptionsGetString(PETSC_NULL,"-file",filename,256,&flg);CHKERRQ(ierr);
  if (!flg) {
    SETERRQ(1,"Must indicate a file name with the -file option.");
  }
  ierr = PetscOptionsGetInt(PETSC_NULL,"-every",&plot_every,&flg);CHKERRQ(ierr);
  if(!flg) {
    plot_every = 1000;
  }
  ierr = PetscOptionsGetInt(PETSC_NULL,"-max_iter",&max_iter,&flg);CHKERRQ(ierr);
  if(!flg) {
    max_iter = 200000;
  }
  if(sizeof(PetscReal) != sizeof(double)) {
    SETERRQ(1,"Please use double precision.\n");
  }
  
  MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  MPI_Comm_size(PETSC_COMM_WORLD, &size);
  ierr = PetscSynchronizedPrintf(PETSC_COMM_WORLD,"[%d] MPI_COMM_size: %d\n", rank, size);CHKERRQ(ierr);
  PetscSynchronizedFlush(PETSC_COMM_WORLD);
  ierr = read_parq_matrix(filename, &A, &pq_info);CHKERRQ(ierr);
  MPI_Barrier(PETSC_COMM_WORLD);
  ierr = MatGetInfo(A, MAT_GLOBAL_SUM, &info);CHKERRQ(ierr);
  //ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD,filename,FILE_MODE_READ,&viewer);CHKERRQ(ierr);
  //ierr = MatLoad(viewer,MATAIJ,&A);CHKERRQ(ierr);
  //ierr = PetscViewerDestroy(viewer);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&x,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&u,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&b,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&d,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetSize(A, &cols, &rows);CHKERRQ(ierr);
  ierr = MatGetLocalSize(A, &lcols, &lrows);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Matrix Size: %d %d nonzero: %.0f fill-ratio: %f\n", cols, rows, info.nz_used, (info.nz_used/cols/rows)*100.0);CHKERRQ(ierr);
  ierr = PetscSynchronizedPrintf(PETSC_COMM_WORLD,"[%d] Matrix Size (local): %d %d\n", rank, lcols, lrows);CHKERRQ(ierr);
  PetscSynchronizedFlush(PETSC_COMM_WORLD);
  ierr = VecSet(u, 1.0/rows);CHKERRQ(ierr);
  ierr = VecSet(b, 0.0);CHKERRQ(ierr);
  ierr = VecSet(x, 0.0);CHKERRQ(ierr);
  ierr = VecSet(d, 0.0);CHKERRQ(ierr);
  
  i=0;
  dist = 1;
  PetscGetTime(&v1);
  //for(i = 0; i < max_iter; ++i) {
  while(dist > 1e-10) {
    i++;
    VecCopy(u, b);
    MatMult(A, u, x);
    if(i % plot_every == 0) {
      VecDot(u, x, &lambda);
      VecAYPX(u, -lambda, x);
      VecNorm(u, NORM_2, &residual);
    }
    power_norm(u, x, &norm);

    //VecMaxPointwiseDivide(b,u,&dist);
    if(i % plot_every == 0) {
      vec_get_dist(b, u, &dist, &dist_elem);
      vec_to_file(u, i, dist, NULL, &pq_info);
      vec_to_file(b, i, dist, "err", &pq_info);
      PetscGetTime(&v2);
      ierr = PetscPrintf(PETSC_COMM_WORLD,"%10d: Norm: %12g r: %12g lambda: %12g dist: %12g (%6d) i/s: %8.4f\n", i, norm, residual, lambda, fabs(dist), dist_elem, plot_every/(v2-v1));CHKERRQ(ierr);
      v1 = v2;
    }
    if(i >= max_iter) {
      break;
    }
  }
  vec_to_file(u, i, dist, NULL, &pq_info);
    
  /* 
     Free work space
  */
  ierr = VecDestroy(u);CHKERRQ(ierr); ierr = VecDestroy(x);CHKERRQ(ierr);
  ierr = VecDestroy(b);CHKERRQ(ierr); ierr = MatDestroy(A);CHKERRQ(ierr);
  ierr = PetscFinalize();CHKERRQ(ierr);
  return 0;
}

