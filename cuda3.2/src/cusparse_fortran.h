/*
 * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:   
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and 
 * international Copyright laws.  Users and possessors of this source code 
 * are hereby granted a nonexclusive, royalty-free license to use this code 
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE 
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH 
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE 
 * OR PERFORMANCE OF THIS SOURCE CODE.  
 *
 * U.S. Government End Users.   This source code is a "commercial item" as 
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of 
 * "commercial computer  software"  and "commercial computer software 
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995) 
 * and is provided to the U.S. Government only as a commercial end item.  
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
 * source code with only those rights set forth herein. 
 *
 * Any use of this source code in individual and commercial software must 
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */
 
typedef size_t ptr_t;

/*
 * Example of Fortran callable thin wrappers for a few CUDA functions. 
 */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int CUDA_MALLOC(ptr_t *devPtr, 
                int *size);

int CUDA_FREE(ptr_t *devPtr);

int CUDA_MEMCPY_FORT2C_INT(ptr_t *devPtr, 
                           const ptr_t *hostPtr, 
                           int *count, 
                           int *kind);
 
int CUDA_MEMCPY_FORT2C_REAL(ptr_t *devPtr, 
                            const ptr_t *hostPtr, 
                            int *count, 
                            int *kind);

int CUDA_MEMCPY_C2FORT_INT(ptr_t *devPtr, 
                           const ptr_t *hostPtr, 
                           int *count, 
                           int *kind);
    
int CUDA_MEMCPY_C2FORT_REAL(ptr_t *devPtr, 
                            const ptr_t *hostPtr, 
                            int *count, 
                            int *kind);
 
int CUDA_MEMSET(ptr_t *devPtr, 
                int *value, 
                int *count);

void GET_SHIFTED_ADDRESS(ptr_t *originPtr, 
                         int *count, 
                         ptr_t *resultPtr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*
 * Example of Fortran callable thin wrappers for CUSPARSE. 
 * Fortran application must allocate and deallocate 
 * GPU memory, and copy data up and down.
 */
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
int CUSPARSE_CREATE(ptr_t *handle);

int CUSPARSE_DESTROY(ptr_t *handle);

int CUSPARSE_GET_VERSION(ptr_t *handle, 
                         int *version);

int CUSPARSE_SET_KERNEL_STREAM(ptr_t *handle, 
                               ptr_t *streamId);

int CUSPARSE_CREATE_MAT_DESCR(ptr_t *descrA);

int CUSPARSE_DESTROY_MAT_DESCR(ptr_t *descrA);

int CUSPARSE_SET_MAT_TYPE(ptr_t *descrA, 
                          int *type);

int CUSPARSE_GET_MAT_TYPE(const ptr_t *descrA);

int CUSPARSE_SET_MAT_FILL_MODE(ptr_t *descrA, 
                               int *fillMode);

int CUSPARSE_GET_MAT_FILL_MODE(const ptr_t *descrA);
 
int CUSPARSE_SET_MAT_DIAG_TYPE(ptr_t *descrA, 
                               int *diagType);

int CUSPARSE_GET_MAT_DIAG_TYPE(const ptr_t *descrA);

int CUSPARSE_SET_MAT_INDEX_BASE(ptr_t *descrA, 
                                int *base);

int CUSPARSE_GET_MAT_INDEX_BASE(const ptr_t *descrA);

int CUSPARSE_SAXPYI(ptr_t *handle, 
                    int *nnz, 
                    float *alpha, 
                    const ptr_t *xVal, 
                    const ptr_t *xInd, 
                    ptr_t *y, 
                    int *idxBase);
    
int CUSPARSE_DAXPYI(ptr_t *handle, 
                    int *nnz, 
                    double *alpha, 
                    const ptr_t *xVal, 
                    const ptr_t *xInd, 
                    ptr_t *y, 
                    int *idxBase);

int CUSPARSE_CAXPYI(ptr_t *handle, 
                    int *nnz, 
                    cuComplex *alpha, 
                    const ptr_t *xVal, 
                    const ptr_t *xInd, 
                    ptr_t *y, 
                    int *idxBase);

int CUSPARSE_ZAXPYI(ptr_t *handle, 
                    int *nnz, 
                    cuDoubleComplex *alpha, 
                    const ptr_t *xVal, 
                    const ptr_t *xInd, 
                    ptr_t *y, 
                    int *idxBase);

int CUSPARSE_SDOTI(ptr_t *handle,
                   int   *nnz,
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   const ptr_t *y,
                   float *resultHostPtr, 
                   int *idxBase);

int CUSPARSE_DDOTI(ptr_t *handle,
                   int   *nnz,
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   const ptr_t *y,
                   double *resultHostPtr, 
                   int *idxBase);

int CUSPARSE_CDOTI(ptr_t *handle,
                   int   *nnz,
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   const ptr_t *y,
                   cuComplex *resultHostPtr, 
                   int *idxBase);

int CUSPARSE_ZDOTI(ptr_t *handle,
                   int   *nnz,
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   const ptr_t *y,
                   cuDoubleComplex *resultHostPtr, 
                   int *idxBase);

int CUSPARSE_CDOTCI(ptr_t *handle,
                    int   *nnz,
                    const ptr_t *xVal, 
                    const ptr_t *xInd, 
                    const ptr_t *y,
                    cuComplex *resultHostPtr, 
                    int *idxBase);

int CUSPARSE_ZDOTCI(ptr_t *handle,
                    int   *nnz,
                    const ptr_t *xVal, 
                    const ptr_t *xInd, 
                    const ptr_t *y,
                    cuDoubleComplex *resultHostPtr, 
                    int *idxBase);

int CUSPARSE_SGTHR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *y, 
                   ptr_t *xVal, 
                   const ptr_t *xInd, 
                   int *idxBase);
    
int CUSPARSE_DGTHR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *y, 
                   ptr_t *xVal, 
                   const ptr_t *xInd, 
                   int *idxBase);

int CUSPARSE_CGTHR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *y, 
                   ptr_t *xVal, 
                   const ptr_t *xInd, 
                   int *idxBase);

int CUSPARSE_ZGTHR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *y, 
                   ptr_t *xVal, 
                   const ptr_t *xInd, 
                   int *idxBase);

int CUSPARSE_SGTHRZ(ptr_t *handle, 
                    int *nnz, 
                    ptr_t *y, 
                    ptr_t *xVal, 
                    const ptr_t *xInd, 
                    int *idxBase);
    
int CUSPARSE_DGTHRZ(ptr_t *handle, 
                    int *nnz, 
                    ptr_t *y, 
                    ptr_t *xVal, 
                    const ptr_t *xInd, 
                    int *idxBase);

int CUSPARSE_CGTHRZ(ptr_t *handle, 
                    int *nnz, 
                    ptr_t *y, 
                    ptr_t *xVal, 
                    const ptr_t *xInd, 
                    int *idxBase);

int CUSPARSE_ZGTHRZ(ptr_t *handle, 
                    int *nnz, 
                    ptr_t *y, 
                    ptr_t *xVal, 
                    const ptr_t *xInd, 
                    int *idxBase);

int CUSPARSE_SSCTR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   ptr_t *y, 
                   int *idxBase);
    
int CUSPARSE_DSCTR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   ptr_t *y, 
                   int *idxBase);

int CUSPARSE_CSCTR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   ptr_t *y, 
                   int *idxBase);

int CUSPARSE_ZSCTR(ptr_t *handle, 
                   int *nnz, 
                   const ptr_t *xVal, 
                   const ptr_t *xInd, 
                   ptr_t *y, 
                   int *idxBase);


int CUSPARSE_SROTI(ptr_t *handle, 
                   int *nnz, 
                   ptr_t *xVal, 
                   const ptr_t *xInd, 
                   ptr_t *y, 
                   float *c, 
                   float *s, 
                   int *idxBase);

int CUSPARSE_DROTI(ptr_t *handle, 
                   int *nnz, 
                   ptr_t *xVal, 
                   const ptr_t *xInd, 
                   ptr_t *y, 
                   double *c, 
                   double *s, 
                   int *idxBase);

int CUSPARSE_SCSRMV(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    float *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *x, 
                    float *beta, 
                    ptr_t *y);
    
int CUSPARSE_DCSRMV(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    double *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *x, 
                    double *beta, 
                    ptr_t *y);

int CUSPARSE_CCSRMV(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    cuComplex *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *x, 
                    cuComplex *beta, 
                    ptr_t *y);

int CUSPARSE_ZCSRMV(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    cuDoubleComplex *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *x, 
                    cuDoubleComplex *beta, 
                    ptr_t *y);

int CUSPARSE_SCSRMM(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    int *k,  
                    float *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *B, 
                    int *ldb, 
                    float *beta, 
                    ptr_t *C, 
                    int *ldc);
                     
int CUSPARSE_DCSRMM(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    int *k,  
                    double *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *B, 
                    int *ldb, 
                    double *beta, 
                    ptr_t *C, 
                    int *ldc);

int CUSPARSE_CCSRMM(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    int *k,  
                    cuComplex *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *B, 
                    int *ldb, 
                    cuComplex *beta, 
                    ptr_t *C, 
                    int *ldc);

int CUSPARSE_ZCSRMM(ptr_t *handle,
                    int *transA, 
                    int *m, 
                    int *n, 
                    int *k,  
                    cuDoubleComplex *alpha,
                    const ptr_t *descrA, 
                    const ptr_t *csrValA, 
                    const ptr_t *csrRowPtrA, 
                    const ptr_t *csrColIndA, 
                    const ptr_t *B, 
                    int *ldb, 
                    cuDoubleComplex *beta, 
                    ptr_t *C, 
                    int *ldc);

int CUSPARSE_SNNZ(ptr_t *handle, 
                  int *dirA, 
                  int *m, 
                  int *n, 
                  const ptr_t *descrA,
                  const ptr_t *A, 
                  int *lda, 
                  ptr_t *nnzPerRowCol, 
                  int *nnzHostPtr);

int CUSPARSE_DNNZ(ptr_t *handle, 
                  int *dirA, 
                  int *m, 
                  int *n, 
                  const ptr_t *descrA,
                  const ptr_t *A, 
                  int *lda, 
                  ptr_t *nnzPerRowCol, 
                  int *nnzHostPtr);

int CUSPARSE_CNNZ(ptr_t *handle, 
                  int *dirA, 
                  int *m, 
                  int *n, 
                  const ptr_t *descrA,
                  const ptr_t *A, 
                  int *lda, 
                  ptr_t *nnzPerRowCol, 
                  int *nnzHostPtr);

int CUSPARSE_ZNNZ(ptr_t *handle, 
                  int *dirA, 
                  int *m, 
                  int *n, 
                  const ptr_t *descrA,
                  const ptr_t *A, 
                  int *lda, 
                  ptr_t *nnzPerRowCol, 
                  int *nnzHostPtr);


int CUSPARSE_SDENSE2CSR(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerRow,                                                 
                        ptr_t *csrValA, 
                        ptr_t *csrRowPtrA, 
                        ptr_t *csrColIndA);
 
int CUSPARSE_DDENSE2CSR(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerRow,                                                 
                        ptr_t *csrValA, 
                        ptr_t *csrRowPtrA, 
                        ptr_t *csrColIndA);

int CUSPARSE_CDENSE2CSR(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerRow,                                                 
                        ptr_t *csrValA, 
                        ptr_t *csrRowPtrA, 
                        ptr_t *csrColIndA);

int CUSPARSE_ZDENSE2CSR(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerRow,                                                 
                        ptr_t *csrValA, 
                        ptr_t *csrRowPtrA, 
                        ptr_t *csrColIndA);


int CUSPARSE_SCSR2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *csrValA, 
                        const ptr_t *csrRowPtrA, 
                        const ptr_t *csrColIndA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_DCSR2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *csrValA, 
                        const ptr_t *csrRowPtrA, 
                        const ptr_t *csrColIndA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_CCSR2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *csrValA, 
                        const ptr_t *csrRowPtrA, 
                        const ptr_t *csrColIndA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_ZCSR2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *csrValA, 
                        const ptr_t *csrRowPtrA, 
                        const ptr_t *csrColIndA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_SDENSE2CSC(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerCol,                                                 
                        ptr_t *cscValA, 
                        ptr_t *cscRowIndA, 
                        ptr_t *cscColPtrA);
 
int CUSPARSE_DDENSE2CSC(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerCol,                                                 
                        ptr_t *cscValA, 
                        ptr_t *cscRowIndA, 
                        ptr_t *cscColPtrA);

int CUSPARSE_CDENSE2CSC(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerCol,                                                 
                        ptr_t *cscValA, 
                        ptr_t *cscRowIndA, 
                        ptr_t *cscColPtrA);

int CUSPARSE_ZDENSE2CSC(ptr_t *handle,
                        int *m, 
                        int *n,  
                        const ptr_t *descrA,                            
                        const ptr_t *A, 
                        int *lda,
                        const ptr_t *nnzPerCol,                                                 
                        ptr_t *cscValA, 
                        ptr_t *cscRowIndA, 
                        ptr_t *cscColPtrA);

int CUSPARSE_SCSC2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *cscValA, 
                        const ptr_t *cscRowIndA, 
                        const ptr_t *cscColPtrA,
                        ptr_t *A, 
                        int *lda);
    
int CUSPARSE_DCSC2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *cscValA, 
                        const ptr_t *cscRowIndA, 
                        const ptr_t *cscColPtrA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_CCSC2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *cscValA, 
                        const ptr_t *cscRowIndA, 
                        const ptr_t *cscColPtrA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_ZCSC2DENSE(ptr_t *handle,
                        int *m, 
                        int *n, 
                        const ptr_t *descrA,  
                        const ptr_t *cscValA, 
                        const ptr_t *cscRowIndA, 
                        const ptr_t *cscColPtrA,
                        ptr_t *A, 
                        int *lda);

int CUSPARSE_XCOO2CSR(ptr_t *handle,
                      const ptr_t *cooRowInd, 
                      int *nnz, 
                      int *m, 
                      ptr_t *csrRowPtr, 
                      int *idxBase);
    
int CUSPARSE_XCSR2COO(ptr_t *handle,
                      const ptr_t *csrRowPtr, 
                      int *nnz, 
                      int *m, 
                      ptr_t *cooRowInd, 
                      int *idxBase);     

int CUSPARSE_SCSR2CSC(ptr_t *handle,
                      int *m, 
                      int *n, 
                      const ptr_t *csrVal, 
                      const ptr_t *csrRowPtr, 
                      const ptr_t *csrColInd, 
                      ptr_t *cscVal, 
                      ptr_t *cscRowInd, 
                      ptr_t *cscColPtr, 
                      int *copyValues, 
                      int *idxBase);

int CUSPARSE_DCSR2CSC(ptr_t *handle,
                      int *m, 
                      int *n, 
                      const ptr_t *csrVal, 
                      const ptr_t *csrRowPtr, 
                      const ptr_t *csrColInd, 
                      ptr_t *cscVal, 
                      ptr_t *cscRowInd, 
                      ptr_t *cscColPtr, 
                      int *copyValues, 
                      int *idxBase);

int CUSPARSE_CCSR2CSC(ptr_t *handle,
                      int *m, 
                      int *n, 
                      const ptr_t *csrVal, 
                      const ptr_t *csrRowPtr, 
                      const ptr_t *csrColInd, 
                      ptr_t *cscVal, 
                      ptr_t *cscRowInd, 
                      ptr_t *cscColPtr, 
                      int *copyValues, 
                      int *idxBase);

int CUSPARSE_ZCSR2CSC(ptr_t *handle,
                      int *m, 
                      int *n, 
                      const ptr_t *csrVal, 
                      const ptr_t *csrRowPtr, 
                      const ptr_t *csrColInd, 
                      ptr_t *cscVal, 
                      ptr_t *cscRowInd, 
                      ptr_t *cscColPtr, 
                      int *copyValues, 
                      int *idxBase);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
