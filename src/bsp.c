#include "global.h"

struct Container *mkContainer(int x, int y, int width, int height) {
  struct Container *container = malloc(sizeof(struct Container));
  container->x = x;
  container->y = y;
  container->width = width;
  container->height = height;
  return container;
}
  

struct BSPNode *mkBSPNode(struct Container *container){
  struct BSPNode *node = malloc(sizeof(struct BSPNode));
  node->container = container;
  node->lNode = NULL;
  node->rNode = NULL;

  return node;
}

int getContainerCenterX(struct Container *container) {
  return container->x + (container->width/2);
}

int getContainerCenterY(struct Container *container) {
  return container->y + (container->height/2);
}

int isLeaf(struct BSPNode *node) {
  return (node->lNode == NULL && node->rNode == NULL);
}

struct Container **randomSplit(struct Container *container) {
  struct Container *c1;
  struct Container *c2;

  int VorH = rand()%2;

  if(VorH) {
    // vertical
    c1 = mkContainer(container->x,
                     container->y,
                     ((rand() % (container->width+1) + 1)),
                     container->height);

    c2 = mkContainer(container->x + c1->width - 1,
                     container->y,
                     container->width - c1->width + 1,
                     container->height);

    float c1_w_ratio = (float) c1->width / (float) c1->height;
    float c2_w_ratio = (float) c2->width / (float) c2->height;
    if (c1_w_ratio < WIDTH_RATIO || c2_w_ratio < WIDTH_RATIO){
      return randomSplit(container);
    }

  } else {
    // horizontal
    c1 = mkContainer(container->x,
                     container->y,
                     container->width,
                     ((rand() % (container->height+1) + 1)));

    c2 = mkContainer(container->x,
                     container->y + c1->height - 1,
                     container->width,
                     container->height - c1->height + 1);

    float c1_h_ratio = (float) c1->height / (float) c1->width;
    float c2_h_ratio = (float) c2->height / (float) c2->width;
    if (c1_h_ratio < HEIGHT_RATIO || c2_h_ratio < HEIGHT_RATIO){
      return randomSplit(container);
    }
  }

  struct Container **containers = malloc(sizeof(struct Container)*2);
  containers[0] = c1;
  containers[1] = c2;

  return containers;
}

struct BSPNode *splitContainer(struct Container *container, int iter) {
  struct BSPNode *root = mkBSPNode(container);
  if(iter != 0) {
    struct Container **sr = randomSplit(container);
    root->lNode = splitContainer(sr[0], iter-1);
    root->rNode = splitContainer(sr[1], iter-1);
  }

  return root;
}
