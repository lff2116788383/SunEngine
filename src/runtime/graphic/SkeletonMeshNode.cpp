#include "SkeletonMeshNode.h"
SkeletonMeshNode::SkeletonMeshNode(const char* path, bool gamma):
	StaticMeshNode(path,gamma)
{
	//LoadBoneData();
}

SkeletonMeshNode::~SkeletonMeshNode()
{
}

void SkeletonMeshNode::LoadBoneData()
{
 
    g_pScene = importer.ReadFile(this->m_flie, aiProcessPreset_TargetRealtime_Fast |
        aiProcess_ConvertToLeftHanded);

    
    assert(g_pScene->mNumMeshes > 0);

  

    for (uint32_t i = 0; i < g_pScene->mNumMeshes; i++)
    {
        const aiMesh* pAiMesh = g_pScene->mMeshes[i];

        auto pMeshNode = &meshes[i];

        // Read in bone data per vertex
        pMeshNode->boneData.resize(pAiMesh->mNumVertices);

        for (uint32_t j = 0; j < pAiMesh->mNumBones; j++)
        {
            aiBone* pBone = pAiMesh->mBones[j];
            std::string boneName(pBone->mName.data);
            uint32_t boneIndex = 0;

            if (m_boneMap.find(boneName) == m_boneMap.end())
            {
                boneIndex = m_numBones;
                m_boneMap[boneName] = m_numBones;
                m_numBones++;

                SEBoneInfo bi = {};
                bi.boneOffsetGLM = aiToGLMFormat(pBone->mOffsetMatrix);
                m_boneInfo.push_back(bi);
            }
            else
            {
                boneIndex = m_boneMap[boneName];
            }

            for (uint32_t k = 0; k < pBone->mNumWeights; k++)
            {
                uint32_t vid = pBone->mWeights[k].mVertexId;
                float weight = pBone->mWeights[k].mWeight;
                // TODO: record all vertices and normalize into 4
                if (weight < 0.0001)
                {
                    continue;
                }
                pMeshNode->boneData[vid].insertData(boneIndex, weight);
            }
        }
    }
}



const aiNodeAnim* FindAnimationNode(const aiAnimation* pAnimations, const std::string& name)
{
    const aiNodeAnim* pAnimNode = nullptr;
    for (uint32_t i = 0; i < pAnimations->mNumChannels; i++)
    {
        const size_t len = strlen(pAnimations->mChannels[i]->mNodeName.data);
        if (strncmp(pAnimations->mChannels[i]->mNodeName.data, name.c_str(), len) == 0)
        {
            pAnimNode = pAnimations->mChannels[i];
            break;
        }
    }

    return pAnimNode;
}

DirectX::XMMATRIX aiToXMMATRIX(aiMatrix4x4 in)
{
    // aiMatrix is row major and so is directx
    return DirectX::XMMATRIX(in.a1, in.a2, in.a3, in.a4,
        in.b1, in.b2, in.b3, in.b4,
        in.c1, in.c2, in.c3, in.c4,
        in.d1, in.d2, in.d3, in.d4);
}



template <typename T>
uint32_t FindKeyframe(float time, uint32_t numKeys, T keys)
{
    uint32_t keyFrame = 0;
    for (uint32_t i = 0; i < numKeys - 1; i++)
    {
        if (time < keys[i + 1].mTime)
        {
            keyFrame = i;
            break;
        }
    }

    return keyFrame;
}

void InterpolateScaling(aiVector3D& v, float time, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1)
    {
        v = pNodeAnim->mScalingKeys[0].mValue;
    }
    else
    {
        const uint32_t keyFrame = FindKeyframe(time, pNodeAnim->mNumScalingKeys, pNodeAnim->mScalingKeys);
        const uint32_t nextFrame = keyFrame + 1;
        assert(nextFrame < pNodeAnim->mNumScalingKeys);
        const float timeBetweenFrames = static_cast<float>(pNodeAnim->mScalingKeys[nextFrame].mTime - pNodeAnim->mScalingKeys[keyFrame].mTime);
        const float offset = static_cast<float>(time - pNodeAnim->mScalingKeys[keyFrame].mTime);
        const float t = offset / timeBetweenFrames;
        assert(t >= 0 && t <= 1.0);
        const aiVector3D& start = pNodeAnim->mScalingKeys[keyFrame].mValue;
        const aiVector3D& end = pNodeAnim->mScalingKeys[nextFrame].mValue;
        aiVector3D delta = end - start;
        v = start + t * delta;
    }
}

void InterpolateRotation(aiQuaternion& q, float time, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumRotationKeys == 1)
    {
        q = pNodeAnim->mRotationKeys[0].mValue;
        q = q.Normalize();
    }
    else
    {
        uint32_t keyFrame = FindKeyframe(time, pNodeAnim->mNumRotationKeys, pNodeAnim->mRotationKeys);
        const uint32_t nextFrame = keyFrame + 1;
        assert(nextFrame < pNodeAnim->mNumRotationKeys);
        const float timeBetweenFrames = static_cast<float>(pNodeAnim->mRotationKeys[nextFrame].mTime - pNodeAnim->mRotationKeys[keyFrame].mTime);
        const float offset = static_cast<float>(time - pNodeAnim->mRotationKeys[keyFrame].mTime);
        const float t = offset / timeBetweenFrames;
        assert(t >= 0 && t <= 1.0);
        const aiQuaternion& start = pNodeAnim->mRotationKeys[keyFrame].mValue;
        const aiQuaternion& end = pNodeAnim->mRotationKeys[nextFrame].mValue;
        aiQuaternion::Interpolate(q, start, end, t);
        q = q.Normalize();
    }
}

void InterpolateTranslation(aiVector3D& v, float time, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1)
    {
        v = pNodeAnim->mPositionKeys[0].mValue;
    }
    else
    {
        uint32_t keyFrame = FindKeyframe(time, pNodeAnim->mNumPositionKeys, pNodeAnim->mPositionKeys);
        const uint32_t nextFrame = keyFrame + 1;
        assert(nextFrame < pNodeAnim->mNumPositionKeys);
        const float timeBetweenFrames = static_cast<float>(pNodeAnim->mPositionKeys[nextFrame].mTime - pNodeAnim->mPositionKeys[keyFrame].mTime);
        const float offset = static_cast<float>(time - pNodeAnim->mPositionKeys[keyFrame].mTime);
        const float t = offset / timeBetweenFrames;
        assert(t >= 0 && t <= 1.0);
        const aiVector3D& start = pNodeAnim->mPositionKeys[keyFrame].mValue;
        const aiVector3D& end = pNodeAnim->mPositionKeys[nextFrame].mValue;
        aiVector3D delta = end - start;
        v = start + t * delta;
    }
}

void SkeletonMeshNode::UpdateNodeHierarchy(float time, const aiScene* pScene, const aiNode* pNode, const aiAnimation* pAnimation, const DirectX::XMMATRIX& parentTansformMatrix)
{
    std::string name(pNode->mName.data);

    // World transformation we are trying to calculate
    DirectX::XMMATRIX currentNodeTransformation = aiToXMMATRIX(pNode->mTransformation);

    const aiNodeAnim* pAnimationNode = FindAnimationNode(pAnimation, name);

    // If we skip this we will get bind pose
    if (pAnimationNode)
    {
        // interpolate scaling
        aiVector3D aiScale;
        InterpolateScaling(aiScale, time, pAnimationNode);
        aiMatrix4x4 scaleM;
        aiMatrix4x4::Scaling(aiScale, scaleM);

        // interpolate rotation
        aiQuaternion aiRotationQ;
        InterpolateRotation(aiRotationQ, time, pAnimationNode);
        aiMatrix4x4 rotationM = aiMatrix4x4(aiRotationQ.GetMatrix());

        // interpolate translation
        aiVector3D aiTranslation;
        InterpolateTranslation(aiTranslation, time, pAnimationNode);
        aiMatrix4x4 translationM;
        aiMatrix4x4::Translation(aiTranslation, translationM);

        aiMatrix4x4 aiCurrentNodeTransformation = translationM * rotationM * scaleM;
        currentNodeTransformation = aiToXMMATRIX(aiCurrentNodeTransformation);
    }

    DirectX::XMMATRIX globalTransformMatrix = parentTansformMatrix * currentNodeTransformation;

    aiMatrix4x4 aiGlobalInverseTransform = pScene->mRootNode->mTransformation;
    aiGlobalInverseTransform = aiGlobalInverseTransform.Inverse();
    DirectX::XMMATRIX globalInverseTransform = aiToXMMATRIX(aiGlobalInverseTransform);

    // note: Not all nodes are bones, but we still have to calculate the transformation in order of the hierarchy
    //       If assimp runs into certain transformations, it will insert helper nodes and break out the 
    //       scale/translate/rotate transforms out of the bone node into separate nodes, and apply animation to those. 
    if (m_boneMap.find(name) != m_boneMap.end())
    {
        uint32_t boneIdx = m_boneMap[name];
        m_boneInfo[boneIdx].finalTransformation =
            globalInverseTransform * globalTransformMatrix * m_boneInfo[boneIdx].boneOffset;
    }

    for (uint32_t i = 0; i < pNode->mNumChildren; i++)
    {
        UpdateNodeHierarchy(time, pScene, pNode->mChildren[i], pAnimation, globalTransformMatrix);
    }
}

void SkeletonMeshNode::UpdateAnimation(float time, uint32_t animIdx)
{
    //std::cout << "animIdx: " << animIdx << std::endl;
  
   /* Assimp::Importer importer;
    g_pScene = importer.ReadFile(this->m_flie, aiProcess_Triangulate);*/
  
    // Get animation node
    assert(g_pScene && g_pScene->mRootNode);
    const aiAnimation* pAnimation = g_pScene->mAnimations[animIdx];     //根据索引或者名字找到要播放的动画

    assert(pAnimation != nullptr);
    // Animation time
    const float ticksPerSecond = pAnimation->mTicksPerSecond;// static_cast<float>(pAnimation->mTicksPerSecond ? pAnimation->mTicksPerSecond : 25.0f);
    const float timeInTicks = time * ticksPerSecond;
    const float animationTime = fmod(timeInTicks, static_cast<float>(pAnimation->mDuration));

    //UpdateNodeHierarchy(animationTime, scene, scene->mRootNode, pAnimation, DirectX::XMMatrixIdentity());
    
    UpdateNodeHierarchy(animationTime, g_pScene, g_pScene->mRootNode, pAnimation, glm::mat4(1.0f));
    
}

void SkeletonMeshNode::UpdateNodeHierarchy(float time, const aiScene* pScene, const aiNode* pNode, const aiAnimation* pAnimation, glm::mat4 parentTansformMatrix)
{
    std::string name(pNode->mName.data);

    // World transformation we are trying to calculate
    glm::mat4 currentNodeTransformation = aiToGLMFormat(pNode->mTransformation);

    const aiNodeAnim* pAnimationNode = FindAnimationNode(pAnimation, name);

    // If we skip this we will get bind pose
    if (pAnimationNode)
    {
        // interpolate scaling
        aiVector3D aiScale;
        InterpolateScaling(aiScale, time, pAnimationNode);
        aiMatrix4x4 scaleM;
        aiMatrix4x4::Scaling(aiScale, scaleM);

        // interpolate rotation
        aiQuaternion aiRotationQ;
        InterpolateRotation(aiRotationQ, time, pAnimationNode);
        aiMatrix4x4 rotationM = aiMatrix4x4(aiRotationQ.GetMatrix());

        // interpolate translation
        aiVector3D aiTranslation;
        InterpolateTranslation(aiTranslation, time, pAnimationNode);
        aiMatrix4x4 translationM;
        aiMatrix4x4::Translation(aiTranslation, translationM);

        aiMatrix4x4 aiCurrentNodeTransformation = translationM * rotationM * scaleM; //计算当前节点的最终矩阵
        currentNodeTransformation = aiToGLMFormat(aiCurrentNodeTransformation); //nodeTransform = Bone->GetLocalTransform();
    }

    glm::mat4 globalTransformMatrix = parentTansformMatrix * currentNodeTransformation;//glm::mat4 globalTransformation = parentTransform * nodeTransform;

    aiMatrix4x4 aiGlobalInverseTransform = pScene->mRootNode->mTransformation;
    aiGlobalInverseTransform = aiGlobalInverseTransform.Inverse();
    glm::mat4 globalInverseTransform = aiToGLMFormat(aiGlobalInverseTransform);

    // note: Not all nodes are bones, but we still have to calculate the transformation in order of the hierarchy
    //       If assimp runs into certain transformations, it will insert helper nodes and break out the 
    //       scale/translate/rotate transforms out of the bone node into separate nodes, and apply animation to those. 
    if (m_BoneInfoMap.find(name) != m_BoneInfoMap.end())
    {
        uint32_t boneIdx = m_BoneInfoMap[name].id;
        glm::mat4 offset = m_BoneInfoMap[name].offset;
        //std::cout << "node name:" << name.c_str() << "th boneInfoMap offset[0][0]" << offset[0][0] << std::endl;
        m_FinalBoneMatrices[boneIdx] = /*globalInverseTransform * */globalTransformMatrix * offset; //m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (uint32_t i = 0; i < pNode->mNumChildren; i++)
    {
        UpdateNodeHierarchy(time, pScene, pNode->mChildren[i], pAnimation, globalTransformMatrix);
    }
}

